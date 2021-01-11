#include "pch.h"
#include "GameState.h"

void GameState::InitPlayer()
{
	this->player = new Player(this->window->getSize().x / 2, this->window->getSize().y / 2);
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

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitVariables();
	this->InitTexture();
	this->InitPlayer();
}
 
GameState::~GameState()
{
}


void GameState::SpawnEnemy()
{
	float posX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
	float posY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));

	this->enemies.push_back(new Enemy(posX, posY));
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
		//delete enemies
		//this->enemies.erase(this->enemies.begin() + i);
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

void GameState::RenderPlayer(RenderTarget* _target)
{
	this->player->Draw(*_target);
}

void GameState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	this->RenderPlayer(_target);
	//this->RenderEnemies(_target);
}