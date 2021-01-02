#include "pch.h"
#include "GameState.h"

GameState::GameState(RenderWindow* _window, stack<State*>* _states)
	: State(_window, _states)
{
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

	//this->player.Render(_target);
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
}