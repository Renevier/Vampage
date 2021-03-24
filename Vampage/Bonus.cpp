#include "pch.h"
#include "Bonus.h"

void Bonus::InitShape()
{
	this->cShape.setRadius(10.f);
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

	if (this->effect == BONUS_EFFECT::NONE)
		this->cShape.setFillColor(Color::Green);
	if (this->effect == BONUS_EFFECT::SHIELD)		
		this->cShape.setFillColor(Color::Blue);
	if (this->effect == BONUS_EFFECT::DASH_MAX)
		this->cShape.setFillColor(Color::Magenta);
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
