#include "pch.h"
#include "HUD.h"

void HUD::InitLifes()
{
	if (!this->lifeTexture.loadFromFile("../Resources/Sprite/Life.png"))
		exit(0);

	this->life.setTexture(&lifeTexture);

	this->life.setSize(Vector2f(
		this->life.getTextureRect().height,
		this->life.getTextureRect().width
	));

	for (int i = 0; i < 6; i++)
	{
		this->life.setPosition(
			i * this->life.getGlobalBounds().width,
			this->life.getGlobalBounds().height / 2
		);

		this->life.setScale(2.f, 2.f);
		this->life.setFillColor(Color(255, 0, 0, 250));

		this->lifes.push_back(this->life);
	}
}

void HUD::InitDashes()
{
	if (!this->dashTexture.loadFromFile("../Resources/Sprite/Dash.png"))
		exit(0);

	this->dash.setTexture(&dashTexture);

	this->dash.setSize(Vector2f(
		this->dash.getTextureRect().height,
		this->dash.getTextureRect().width
	));

	for (int i = 0; i < 6; i++)
	{
		this->dash.setPosition(
			i * this->dash.getGlobalBounds().width,
			this->window->getSize().y - this->dash.getGlobalBounds().height
		);

		this->life.setFillColor(Color(0, 250, 0, 250));

		this->dashes.push_back(this->dash);
	}
}

void HUD::InitTextLevel()
{
	if (!this->font.loadFromFile("../Resources/Fonts/SteampunkMachineryFont-Regular.ttf"))
		exit(0);

	this->textLevel.setFont(this->font);

	this->textLevel.setFillColor(Color::Red);
	this->textLevel.setCharacterSize(60);
	this->textLevel.setString("Level 1");
	this->textLevel.setOrigin(Vector2f(
		this->textLevel.getGlobalBounds().width / 2,
		this->textLevel.getGlobalBounds().height / 2
	));

	this->textLevel.setPosition(Vector2f(
		this->window->getSize().x - this->textLevel.getGlobalBounds().width,
		this->textLevel.getGlobalBounds().height
	));
}

HUD::HUD(Player* _player, RenderWindow* _window)
	:window(_window), player(_player)
{
	this->InitTextLevel();
	this->InitLifes();
	this->InitDashes();
}

void HUD::UpdateLifes()
{
	for (int i = 1; i <= this->lifes.size(); i++)
	{
		if(i > this->player->GetHP())
			this->lifes[i - 1].setFillColor(Color(255, 0, 0, 50));
		else
			this->lifes[i - 1].setFillColor(Color(255, 0, 0, 255));
	}

}

void HUD::UpdateDashes()
{
	for (int i = 1; i <= this->dashes.size(); i++)
	{
		if (i > this->player->GetNbDash())
			this->dashes[i - 1].setFillColor(Color(0, 250, 0, 50));
		else
			this->dashes[i - 1].setFillColor(Color(0, 255, 255, 255));
	}
}

void HUD::UpdateTextLevel(int _lvl)
{
	this->textLevel.setString("Level " + to_string(_lvl));
}

void HUD::Update(int _lvl)
{
	if (!this->player)
		return;

	this->UpdateLifes();
	this->UpdateDashes();
	this->UpdateTextLevel(_lvl);
}

void HUD::Draw(RenderTarget& _target)
{
	_target.draw(this->textLevel);

	for (auto it : this->lifes)
		_target.draw(it);

	for (auto it : this->dashes)
		_target.draw(it);
}
