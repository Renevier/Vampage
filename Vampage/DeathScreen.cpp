#include "pch.h"
#include "DeathScreen.h"

void DeathScreen::InitBc(RenderWindow* _window)
{
	this->bc.setSize(Vector2f(500, _window->getSize().y));
	this->bc.setFillColor(Color(20, 20, 20, 100));
	this->bc.setOutlineColor(Color::Red);
	this->bc.setOutlineThickness(1.f);

	this->bc.setOrigin(Vector2f(
		this->bc.getGlobalBounds().width / 2,
		this->bc.getGlobalBounds().height / 2
	));

	this->bc.setPosition(Vector2f(
		_window->getSize().x / 2,
		_window->getSize().y / 2
	));
}

void DeathScreen::InitText(RenderWindow* _window)
{
	if (!this->font.loadFromFile("../Resources/Fonts/SteampunkMachineryFont-Regular.ttf"))
		exit(0);

	this->deathTxt.setFont(this->font);
	this->deathTxt.setFillColor(Color::Red);
	this->deathTxt.setCharacterSize(60);
	this->deathTxt.setString("YOU ARE DEAD");
	this->deathTxt.setOrigin(Vector2f(
		this->deathTxt.getGlobalBounds().width / 2,
		this->deathTxt.getGlobalBounds().height / 2
	));

	this->deathTxt.setPosition(Vector2f(
		this->bc.getPosition().x,
		this->bc.getPosition().y - this->bc.getGlobalBounds().height / 2 + this->deathTxt.getGlobalBounds().height / 2
	));
}

DeathScreen::DeathScreen(RenderWindow* _window)
{
	this->InitBc(_window);
	this->InitText(_window);
}

void DeathScreen::AddButtons(const string key, float x, float y, const string text)
{
	this->buttons.emplace(key, new Button(
		x, y, 250, 40,
		&this->font, text, 50,
		Color(255, 0, 0, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0)));
}

void DeathScreen::Update(const Vector2f& _mousePos)
{
}

void DeathScreen::Draw(RenderTarget* _target)
{
	_target->draw(this->bc);

	_target->draw(this->deathTxt);

	for (auto it : this->buttons)
		it.second->Render(*_target);
}
