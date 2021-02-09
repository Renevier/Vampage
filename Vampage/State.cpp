#include "pch.h"
#include "State.h"

void State::InitView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y));
	this->view.setCenter(static_cast<float>(this->window->getSize().x / 2.f),
		static_cast<float>(this->window->getSize().y / 2.f));
}

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