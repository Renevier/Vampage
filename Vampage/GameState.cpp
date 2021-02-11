#include "pch.h"
#include "GameState.h"

void GameState::InitPlayer()
{
	this->player = make_unique<Player>(&this->mousePosView, this->window->getSize().x / 2, this->window->getSize().y / 2);
}

void GameState::InitTexture()
{

}

void GameState::InitVariables()
{
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 15;
}

void GameState::InitView()
{
	this->view.setSize(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	);

	this->view.setCenter(
		this->player->GetPos().x,
		this->player->GetPos().y
	);

	this->window->setView(this->view);
}

void GameState::InitSpawnArea()
{
	this->spawnArea.setRadius(1000.f);
	this->spawnArea.setOrigin(
		this->spawnArea.getRadius(),
		this->spawnArea.getRadius()
	);
	this->spawnArea.setFillColor(Color::Transparent);
	this->spawnArea.setPosition(this->view.getCenter());

	this->spawnArea.setOutlineThickness(1.f);
	this->spawnArea.setOutlineColor(Color::Yellow);
}

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitVariables();
	this->InitTexture();
	this->InitPlayer();
	this->InitView();
	this->InitSpawnArea();
}

GameState::~GameState() {}


void GameState::SpawnEnemy()
{
	float posX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
	float posY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));

	if (!this->player->GetNoSpawnArea().getGlobalBounds().contains(Vector2f(posX, posY)))
	{
		this->enemies.push_back(make_shared<Enemy>(posX, posY, &this->player->GetPos()));
	}
}

void GameState::KillEnemy()
{
	//for (size_t i = 0; i < this->player->GetBullets().size(); i++)
	//{
	//	for (size_t j = 0; j < this->enemies.size(); j++)
	//	{
	//		if (this->enemies[j]->GetBounds().intersects(this->player->GetBullets().at(i)->GetBounds()))
	//		{
	//			//this->player->GetBullets().erase(this->player->GetBullets().begin() + i);
	//			this->enemies.erase(this->enemies.begin() + j);

	//			break;
	//		}
	//	}
	//}
	auto it = this->player->GetBullets().begin();
	auto it2 = this->enemies.begin();

	if (/*(*it) &&*/ (&it) != NULL)
	{
		for (it; it != this->player->GetBullets().end() - 1; it++)
		{
			if (/*(*it2) && */(&it2) != NULL)
			{
				for (it2; it2 != enemies.end() - 1; it2++)
				{
					if ((*it)->GetBounds().intersects((*it2)->GetBounds()))
					{
						if (it2 != this->enemies.begin())
							it2--;

						this->enemies.erase(it2);
					}
				}
			}

		}
	}
}

void GameState::UpdateView()
{
	this->view.setCenter(this->player->GetPos().x,
		this->player->GetPos().y);

	this->window->setView(this->view);
}

void GameState::UpdateSpawnArea()
{
	this->spawnArea.setPosition(this->view.getCenter());
}

void GameState::UpdateInput(const float& _dt)
{
}

void GameState::UpdateEnemies(const float& _dt)
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->SpawnEnemy();
			this->enemySpawnTimer = 0.f;
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
	this->UpdateView();
	this->UpdateSpawnArea();
	this->UpdateMousePosition();

	this->UpdateEnemies(_dt);
	this->player->Update(_dt);

}

void GameState::EndState()
{
}

void GameState::PauseMenu()
{
}

void GameState::RenderSpawnArea(RenderTarget* _target)
{
	_target->draw(this->spawnArea);
}

void GameState::RenderEnemies(RenderTarget* _target)
{
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->Draw(*_target);
	}
}

void GameState::RenderPlayer(RenderTarget* _target)
{
	this->player->Draw(*_target);
}

void GameState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	this->RenderEnemies(_target);
	this->RenderPlayer(_target);
	//this->RenderSpawnArea(_target);
}