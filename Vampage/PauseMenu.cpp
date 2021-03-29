#include "pch.h"
#include "PauseMenu.h"

void PauseMenu::InitBackground(RenderWindow& window)
{
	this->background.setSize(Vector2f(
		window.getSize().x,
		window.getSize().y)
	);
	this->background.setFillColor(Color(20, 20, 20, 100));
}

void PauseMenu::InitButtonContainer(RenderWindow& window)
{
	this->buttonContainer.setPosition(Vector2f(
		0.f,
		0.f)
	);
	this->buttonContainer.setSize(Vector2f(
		window.getSize().x / 4.f,
		window.getSize().y)
	);

	this->buttonContainer.setFillColor(Color(20, 20, 20, 100));
}

void PauseMenu::InitText(Font& font)
{
	this->menuText.setFont(font);
	this->menuText.setFillColor(Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->buttonContainer.getPosition().x + this->buttonContainer.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->buttonContainer.getPosition().y + 40.f
	);
}

void PauseMenu::InitDescriptionContainer(RenderWindow& window)
{
	this->descriptionContainer.setSize(Vector2f(
		window.getSize().x / 4.f,
		window.getSize().y / 4.f
	));

	this->descriptionContainer.setOrigin(
		this->descriptionContainer.getGlobalBounds().width / 2,
		this->descriptionContainer.getGlobalBounds().height / 2
	);

	this->descriptionContainer.setFillColor(Color(20, 20, 20, 100));
	this->descriptionContainer.setPosition(Vector2f(
		window.getSize().x / 2,
		window.getSize().y / 2)
	);
}

PauseMenu::PauseMenu(RenderWindow& window, Font& _font)
	:font(_font)
{
	this->InitBackground(window);
	this->InitButtonContainer(window);
	this->InitDescriptionContainer(window);
	this->InitText(_font);
	this->InitDescriptionText(_font);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void PauseMenu::Update(const Vector2i& mousePosWindow)
{
	
}

void PauseMenu::Render(RenderTarget& target, bool wantSave)
{
}

void PauseMenu::AddButton(const string key, float x, float y, const string text)
{
}

bool PauseMenu::IsButtonPressed(const string key)
{
	return false;
}
