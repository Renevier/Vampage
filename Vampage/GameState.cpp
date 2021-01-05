#include "pch.h"
#include "GameState.h"

void GameState::InitTexture()
{
	
}

void GameState::InitEnemies()
{
	this->enemy = new Enemy();
}

void GameState::InitVariables()
{
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitVariables();
	this->InitTexture();
	this->InitEnemies();
}
 
GameState::~GameState()
{
	delete this->enemy;
}


void GameState::SpawnEnemy()
{
	this->enemy->SetPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy->GetGlobalBounds().width)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy->GetGlobalBounds().height))
	);

	this->enemy->SetFillColor(Color::Green);

	this->enemies.push_back(this->enemy);
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

	//Move the enemies
	for (auto& e : this->enemies)
	{
		e->Move(0.f, .5f);
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
	for (auto& e : this->enemies)
	{
		e->Draw(*_target);
	}
}

void GameState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	this->RenderEnemies(_target);
}