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
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 15;
}

void GameState::InitView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y));
	this->view.setCenter(this->player->GetPos().x,
		this->player->GetPos().y);

	this->window->setView(this->view);
}

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitVariables();
	this->InitTexture();
	this->InitPlayer();
	this->InitView();
}

GameState::~GameState()
{
	delete this->player;
}


void GameState::SpawnEnemy()
{
	float posX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
	float posY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));

	if (!this->player->GetNoSpawnArea().getGlobalBounds().contains(Vector2f(posX, posY)))
	{
		this->enemies.push_back(new Enemy(posX, posY, &this->player->GetPos()));
	}
}

void GameState::UpdateView()
{
	this->view.setCenter(this->player->GetPos().x,
		this->player->GetPos().y);

	this->window->setView(this->view);
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

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->Update(_dt);
	}
}

void GameState::Update(const float& _dt)
{
	this->UpdateView();
	this->UpdateEnemies(_dt);
	this->UpdateMousePosition();

	this->player->Update(_dt);

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
	this->RenderEnemies(_target);
}