#include "pch.h"
#include "GameState.h"

void GameState::InitTexture()
{
	if (!this->textures["PLAYER"].loadFromFile("../Resources/Sprite/Player_idle.png"))
		throw "ERROR game state could not load idle texture";
}

void GameState::InitPlayer()
{
	this->player = new Player(50, 50, this->textures["PLAYER"]);
}

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
	this->InitTexture();
	this->InitPlayer();
}

void GameState::UpdateInput(const float& _dt)
{
}

void GameState::Update(const float& _dt)
{
	this->UpdateMousePosition();
	this->UpdateInput(_dt);
	this->CheckForPause();
	this->PauseMenu();
}

void GameState::Render(RenderTarget* _target)
{
	if (!_target)
		_target = this->window;

	this->player->Render(*_target);
}

void GameState::UpdateState()
{
}

void GameState::EndState()
{
}

void GameState::CheckForPause()
{}

void GameState::PauseMenu()
{
}

GameState::~GameState()
{
	delete this->player;
}