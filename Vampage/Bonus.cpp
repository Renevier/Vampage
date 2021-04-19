#include "pch.h"
#include "Bonus.h"

void Bonus::InitShape()
{
	this->cShape.setRadius(15.f);
	this->cShape.setOrigin(Vector2f(this->cShape.getGlobalBounds().width / 2, this->cShape.getGlobalBounds().height / 2));
}

void Bonus::InitPosition(float _x, float _y)
{
	this->cShape.setPosition(Vector2f(_x, _y));
}

Bonus::Bonus(float _x, float _y, BONUS_EFFECT _effect)
{
	this->InitShape();
	this->InitPosition(_x, _y);

	this->effect = _effect;

	if (this->effect == BONUS_EFFECT::NONE || this->effect == BONUS_EFFECT::SHIELD)
	{
		if (!this->bonusTexture.loadFromFile("../Resources/Sprite/Heal.png"))
			exit(0);

		this->cShape.setTexture(&bonusTexture);
	}
	if (this->effect == BONUS_EFFECT::DASH_MAX)
	{
		if (!this->bonusTexture.loadFromFile("../Resources/Sprite/Dash.png"))
			exit(0);

		this->cShape.setTexture(&bonusTexture);
	}
	if (this->effect == BONUS_EFFECT::SHOOTING_DISTANCE)
		this->cShape.setFillColor(Color::Red);
	
}

void Bonus::Move(const float& _dt)
{
}

void Bonus::Update(const float& _dt)
{
}

void Bonus::Draw(RenderTarget& _target)
{
	_target.draw(this->cShape);
}
