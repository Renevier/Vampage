#include "pch.h"
#include "Pause.h"

void Pause::InitBc(RenderWindow* _window)
{
	this->bc.setSize(Vector2f(
		_window->getSize().x / 4,
		_window->getSize().y));

	this->bc.setFillColor(Color(10, 10, 10, 150));
}

Pause::Pause(RenderWindow* _window)
{
	if (!this->font.loadFromFile("../Resources/Fonts/BLOODY.ttf"))
		exit(0);

	this->InitBc(_window);
}

void Pause::AddButtons(const string key, float x, float y, const string text)
{
	this->buttons.emplace(key, new Button(
		x, y, 250, 40,
		&this->font, text, 50,
		Color(255, 0, 0, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0)));
}

void Pause::Update(const Vector2f& _mousePos)
{
}

void Pause::Draw(RenderTarget* _target)
{
	_target->draw(this->bc);

	for (auto it : this->buttons)
		it.second->Render(*_target);
}
