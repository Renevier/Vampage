#include "pch.h"
#include "GameState.h"

void GameState::InitPlayer()
{
	this->player = new Player(&this->mousePosView, this->window->getSize().x / 2, this->window->getSize().y / 2);
}

void GameState::InitTexture()
{

}

void GameState::InitVariables()
{
	this->level = 1;
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->cptEnemies = this->level * 10;
	this->timerForNextLevel = 0.f;
	this->goToNextLevel = false;
}

void GameState::InitEndLevel()
{
	this->levelEnded = make_unique<LevelEnded>(this->window);
}

void GameState::InitHUD()
{
	this->hud = new HUD(this->player, this->window);
}

void GameState::InitPause()
{
	this->pause = make_unique<Pause>(this->window);

	this->InitPauseButtons();
}

void GameState::InitPauseButtons()
{
	this->pause.get()->AddButtons("GAME_RETURN", 100.f, 300.f, "Resume the game");
	this->pause.get()->AddButtons("EXIT_GAME", 100.f, 600.f, "Quit");
}

void GameState::InitDeathScreen()
{
	this->deathScreen = make_unique<DeathScreen>(this->window);

	this->InitDeathScreenButtons();
}

void GameState::InitDeathScreenButtons()
{
	this->deathScreen.get()->AddButtons("MENU_RETURN", this->window->getSize().x / 2 - 100.f, 450.f, "Back to menu");
	this->deathScreen.get()->AddButtons("QUIT", this->window->getSize().x / 2 - 100.f, 800.f, "Quit the game");
}

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states), bPause(false), isDead(false)
{
	this->InitVariables();
	this->InitTexture();
	this->InitEndLevel();
	this->InitPlayer();
	this->InitHUD();
	this->InitPause();
	this->InitDeathScreen();
}

GameState::~GameState()
{
	delete this->bonus;
	delete this->player;
}

void GameState::DropBonus(float _x, float _y)
{
	if (this->level == 1)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::NONE);

	if (this->level == 2)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::DASH_MAX);

	if (this->level == 3)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::NONE);

	if (this->level == 4)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::SHOOTING_DISTANCE);

	if (this->level >= 5)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::NONE);
}

void GameState::SpawnEnemy()
{
	float posX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
	float posY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));

	if (!this->player->GetNoSpawnArea().getGlobalBounds().contains(Vector2f(posX, posY)))
	{
		int id = static_cast<float>(rand() % 3);

		if (id == 0)
			this->enemies.push_back(make_unique<Enemy>(this->window, posX, posY, this->player));
		if (id == 1)
			this->enemies.push_back(make_unique<RangedEnnemy>(this->window, posX, posY, this->player));
		else
			this->enemies.push_back(make_unique<BouncedEnemy>(this->window, posX, posY, this->player));
	}
	else
		this->cptEnemies++;

}

void GameState::SpawnBoss()
{
	this->boss = make_unique<Boss>(this->window, this->window->getSize().x / 2,
		this->window->getSize().y / 2, this->player);
}

void GameState::KillEnemy()
{
	for (auto it = this->player->GetBullets().begin(); it != this->player->GetBullets().end(); it++)
	{
		for (auto it2 = this->enemies.begin(); it2 != enemies.end(); it2++)
		{
			if ((*it)->GetBounds().intersects((*it2)->GetBounds()))
			{
				it2->get()->ReceiveDamage(1);

				if (it2->get()->GetHp() <= 0)
				{
					this->points += 10;
					it2 = this->enemies.erase(it2);
				}

				if (this->cptEnemies == 0 && it2->get()->GetHp() <= 0) {
					this->DropBonus((*it2)->GetShape().getPosition().x, (*it2)->GetShape().getPosition().y);
				}

				break;
			}
		}
	}
}

void GameState::UpdatePauseButton()
{
	for (auto it : this->pause.get()->GetButtons())
		it.second->Update(this->mousePosView);

	if (this->pause.get()->GetButtons().at("GAME_RETURN")->IsPressed())
		this->bPause = false;

	if (this->pause.get()->GetButtons().at("EXIT_GAME")->IsPressed())
		this->states->push(new MainMenuState(this->window, this->states));
}

void GameState::UpdateDeathButton()
{
	for (auto it : this->deathScreen.get()->GetButtons())
		it.second->Update(this->mousePosView);

	if (this->deathScreen.get()->GetButtons().at("MENU_RETURN")->IsPressed())
		this->states->push(new MainMenuState(this->window, this->states));

	if (this->deathScreen.get()->GetButtons().at("QUIT")->IsPressed())
		exit(0);
}

void GameState::UpdateInput(const float& _dt)
{
}

void GameState::UpdateEnemies(const float& _dt)
{
	if (this->enemies.size() < this->cptEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->SpawnEnemy();
			this->enemySpawnTimer = 0.f;
			this->cptEnemies--;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	for (auto i = 0; i < this->enemies.size(); i++)
		this->enemies.at(i)->Update(_dt);

}

void GameState::UpdatePlayer(const float& _dt)
{
	this->player->Update(_dt);
	this->KillEnemy();

	if (this->player->GetHP() <= 0)
	{
		this->player = nullptr;
		delete this->player;
	}
}

void GameState::Update(const float& _dt)
{	
	this->UpdateMousePosition();

	if (!this->player)
	{
		isDead = true;
		this->UpdateDeathButton();
	}
	else
		this->isDead = false;

	if (Keyboard::isKeyPressed(Keyboard::P))
		this->bPause = true;

	if (!this->bPause && !this->isDead)
	{
		this->CheatCode();
		this->hud->Update(this->level);

		if (!this->player)
			return;

		this->UpdateMousePosition();

		if (!this->bonus)
		{
			if (this->boss)
				this->boss.get()->Update(_dt);

			this->UpdateEnemies(_dt);
			this->UpdatePlayer(_dt);
		}
		else
		{
			if (!this->goToNextLevel)
			{
				this->UpdateEnemies(_dt);
				this->UpdatePlayer(_dt);
				this->PickedUpBonus(_dt);
			}
			else
			{
				this->timerForNextLevel += _dt;
				this->levelEnded->UpdateTimer(this->timerForNextLevel);
				this->levelEnded->UpdateScore(this->points);

				if (this->timerForNextLevel >= 5.f)
				{
					this->timerForNextLevel = 0.f;
					this->bonus = nullptr;
					this->goToNextLevel = false;
					this->player->SetNbDash();
					this->player->CheckBonus();
				}
			}
		}
	}
	else if (this->bPause)
		this->UpdatePauseButton();
}

void GameState::EndState()
{
	this->states->pop();
}

void GameState::PauseMenu()
{
}

void GameState::CheatCode()
{
	if (Keyboard::isKeyPressed(Keyboard::Numpad1))
	{
		this->enemies.clear();
		this->cptEnemies = 0;

		this->DropBonus(
			this->window->getSize().x / 2,
			this->window->getSize().y / 2
		);
	}
}

void GameState::PickedUpBonus(const float& _dt)
{
	if (this->player->GetShape().getGlobalBounds().intersects(this->bonus->GetBounds()))
	{
		if (this->bonus->GetEffect() == BONUS_EFFECT::NONE)
			this->player->SetGainHp(false);

		this->player->AddBonus(this->bonus);
		this->goToNextLevel = true;
		this->level++;

		this->cptEnemies = this->level * 10 - 5;

	}
}

void GameState::RenderEnemies(RenderTarget* _target)
{
	for (auto& it : this->enemies)
		it->Draw(*_target);
}

void GameState::RenderBoss(RenderTarget* _target)
{
	this->boss.get()->Draw(*_target);
}

void GameState::RenderPlayer(RenderTarget* _target)
{
	this->player->Draw(*_target);
}

void GameState::RenderBonus(RenderTarget* _target)
{
	this->bonus->Draw(*_target);
}

void GameState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	if (this->bPause)
		this->pause->Draw(_target);

	if (this->isDead)
		this->deathScreen->Draw(_target);

	this->hud->Draw(*_target);

	if (this->player)
		this->RenderPlayer(_target);

	this->RenderEnemies(_target);

	if (this->boss)
		this->RenderBoss(_target);

	if (this->bonus)
	{
		if (this->goToNextLevel)
			this->levelEnded->Render(_target);
		else
			this->RenderBonus(_target);
	}
}