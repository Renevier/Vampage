#include "pch.h"
#include "State.h"

State::State(RenderWindow* _window, stack<State*>* _states)
{
	this->window = _window;
	this->states = _states;

	this->Quit = false;
}

void State::UpdateMousePosition()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(mousePosWindow);
}