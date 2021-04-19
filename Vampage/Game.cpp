#include "pch.h"
#include "Game.h"

void Game::InitWindow()
{
	this->window = new RenderWindow(VideoMode::getDesktopMode(), "Vampage", Style::Fullscreen);

	this->window->setFramerateLimit(60);
}


void Game::InitState()
{
	this->states.emplace(new MainMenuState(this->window, &this->states));
}

Game::Game()
{
	this->InitWindow();
	this->InitState();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::Run()
{
	while (this->window->isOpen())
	{
		this->UpdateDt();
		this->Update();
		this->Render();
	}
}

void Game::UpdateDt()
{
	this->deltaTime = this->clock.restart().asSeconds();
}

void Game::Update()
{
	this->UpdateEventSFML();

	if (!this->states.empty())
	{
		this->states.top()->Update(this->deltaTime);

		if (this->states.top()->GetQuit())
		{
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->window->close();
	}

}

void Game::UpdateEventSFML()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == Event::Closed)
			this->window->close();
	}
}

void Game::Render()
{
	this->window->clear();

	//Display state
	if (!this->states.empty())
		this->states.top()->Render(this->window);

	this->window->display();
}