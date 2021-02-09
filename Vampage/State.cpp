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

	//this->InitView();
}

void State::UpdateMousePosition()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	//this->window->setView(this->view);
	this->mousePosView = this->window->mapPixelToCoords(mousePosWindow);
	//this->window->setView(this->window->getDefaultView());

	cout << this->mousePosView.x << " " << this->mousePosView.y << endl;
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