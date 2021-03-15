#include "pch.h"
#include "State.h"

State::State(RenderWindow* _window, stack<State*>* _states)
{
	this->window = _window;
	this->states = _states;

	this->Quit = false;
	this->pause = false;
}

void State::UpdateMousePosition()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(mousePosWindow);
}

const bool& State::GetQuit() const
{
	return this->Quit;
}

const bool& State::GetPause() const
{
	return this->pause;
}

State::~State()
{
}