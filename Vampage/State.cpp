#include "State.h"

void State::InitView()
{
	this->view.setSize(this->window->getSize().x, this->window->getSize().y);
	this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

State::State(RenderWindow* _window, map<string, int>* _supportedKeys, stack<State*>* _states)
{
	this->window = _window;
	this->supportedKeys = _supportedKeys;
	this->states = _states;

	this->Quit = false;
	this->pause = false;

	this->InitView();
}

void State::UpdateMousePosition()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->window->setView(this->view);
	this->mousePosView = this->window->mapPixelToCoords(mousePosWindow);
	this->window->setView(this->window->getDefaultView());
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