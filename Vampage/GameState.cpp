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
	this->maxEnemies = 30;
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
	this->InitSpawnArea();
}

GameState::~GameState() {}

void GameState::DropBonus(float _x, float _y)
{
	this->bonus.push_back(make_unique<Bonus>(_x, _y));
}

void GameState::SpawnEnemy()
{
	float posX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
	float posY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));

	if (!this->player->GetNoSpawnArea().getGlobalBounds().contains(Vector2f(posX, posY)))
		this->enemies.push_back(make_unique<Enemy>(posX, posY, &this->player->GetPos()));
}

void GameState::KillEnemy()
{ 
	for (auto it = this->player->GetBullets().begin(); it != this->player->GetBullets().end(); it++)
	{
		for (auto it2 = this->enemies.begin(); it2 != enemies.end(); it2++)
		{
			if ((*it)->GetBounds().intersects((*it2)->GetBounds()))
			{
				this->DropBonus((*it)->GetShape().getPosition().x, (*it)->GetShape().getPosition().y);
				it2 = this->enemies.erase(it2);

				if (it2 != this->enemies.begin())
					it2--;

				break;
			}
		}
	}
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
	for (auto &it : this->enemies)
		it->Draw(*_target);
}

void GameState::RenderPlayer(RenderTarget* _target)
{
	this->player->Draw(*_target);
}

void GameState::RenderBonus(RenderTarget* _target)
{
	for (auto &it: this->bonus)
		it->Draw(*_target);
}

void GameState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	this->RenderPlayer(_target);
	this->RenderSpawnArea(_target);
	this->RenderBonus(_target);
	this->RenderEnemies(_target);
}