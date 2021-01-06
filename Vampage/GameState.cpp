#include "pch.h"
#include "GameState.h"

void GameState::InitTexture()
{
	
}

void GameState::InitVariables()
{
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20;
}

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitVariables();
	this->InitTexture();
}
 
GameState::~GameState()
{
}


void GameState::SpawnEnemy()
{
	this->enemies.push_back(new Enemy(this->window));
}

void GameState::UpdateInput(const float& _dt)
{
}

void GameState::UpdateEnemies()
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

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->Move(0.f, 10.f);

		//Check if the enemy is past the bottom of the screen
		if (this->enemies[i]->GetPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);

		}
	}
}

void GameState::Update(const float& _dt)
{
	this->UpdateEnemies();
	this->UpdateMousePosition();
	this->UpdateInput(_dt);

}

void GameState::EndState()
{
}

void GameState::PauseMenu()
{
}

void GameState::RenderEnemies(RenderTarget* _target)
{
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->Draw(*_target);
	}
}

void GameState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	this->RenderEnemies(_target);
}