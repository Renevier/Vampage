#include "pch.h"
#include "HUD.h"

void HUD::InitLifes(RenderWindow* _window)
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
		this->life.setFillColor(Color(255, 0, 0, 150));

		this->lifes.push_back(this->life);
	}
}

HUD::HUD(Player* _player, RenderWindow* _window)
	:window(_window), player(_player)
{
	this->InitLifes(_window);
}

void HUD::UpdateLifes()
{
	this->life.setFillColor(Color(255, 0, 0, 150));

	for (unsigned int i = 0; i < this->player->GetHP(); i++)
		this->lifes[i].setFillColor(Color(255, 0, 0, 250));
}

void HUD::Update()
{
	if (!this->player)
		return;

	this->UpdateLifes();
}

void HUD::Draw(RenderTarget& _target)
{
	for (auto it : this->lifes)
		_target.draw(it);
}
