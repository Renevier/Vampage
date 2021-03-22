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

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitVariables();
	this->InitTexture();
	this->InitEndLevel();
	this->InitPlayer();
}

GameState::~GameState()
{
	delete this->bonus;
}

void GameState::DropBonus(float _x, float _y)
{
	if(this->level == 1)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::SHIELD);

	if (this->level == 2)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::DASH_MAX);

	if (this->level == 3)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::NONE);

	if (this->level == 4)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::SHOOTING_DISTANCE);

	if (this->level == 5)
		this->bonus = new Bonus(_x, _y, BONUS_EFFECT::NONE);
}

void GameState::SpawnEnemy()
{
	float posX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
	float posY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));

	if (!this->player->GetNoSpawnArea().getGlobalBounds().contains(Vector2f(posX, posY)))
	{
		int id = static_cast<float>(rand() % 3);

		if(id == 0)
			this->enemies.push_back(make_unique<Enemy>(this->window, posX, posY, this->player));
		if (id == 1)
			this->enemies.push_back(make_unique<RangedEnnemy>(this->window, posX, posY, this->player));
		else
			this->enemies.push_back(make_unique<BouncedEnemy>(this->window, posX, posY, this->player));
	}
	else
		this->cptEnemies++;

}

void GameState::KillEnemy()
{
	for (auto it = this->player->GetBullets().begin(); it != this->player->GetBullets().end(); it++)
	{
		for (auto it2 = this->enemies.begin(); it2 != enemies.end(); it2++)
		{
			if ((*it)->GetBounds().intersects((*it2)->GetBounds()))
			{
				this->points += 10;

				/*if (it2 != this->enemies.begin())
					it2--;*/

				it2 = this->enemies.erase(it2);

				if (this->cptEnemies == 0) {
					this->DropBonus((*it)->GetShape().getPosition().x, (*it)->GetShape().getPosition().y);
				}

				break;
			}
		}
	}
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

	this->KillEnemy();
}

void GameState::Update(const float& _dt)
{
	this->UpdateMousePosition();

	if (!this->bonus)
	{
		this->UpdateEnemies(_dt);
		this->player->Update(_dt);
	}
	else
	{
		if (!this->goToNextLevel)
		{
			this->UpdateEnemies(_dt);
			this->player->Update(_dt);
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

void GameState::EndState()
{
	this->states->pop();
}

void GameState::PauseMenu()
{
}

void GameState::PickedUpBonus(const float& _dt)
{
	if (this->player->GetShape().getGlobalBounds().intersects(this->bonus->GetBounds()))
	{
		this->player->AddBonus(this->bonus);
		this->goToNextLevel = true;
		this->level++;

		if(this->level <= 5)
			this->cptEnemies = this->level * 10 - 5;
	}
}

void GameState::RenderEnemies(RenderTarget* _target)
{
	for (auto& it : this->enemies)
		it->Draw(*_target);
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

	this->RenderPlayer(_target);
	this->RenderEnemies(_target);

	if (this->bonus)
	{
		if (this->goToNextLevel)
			this->levelEnded->Render(_target);
		else
			this->RenderBonus(_target);
	}

}