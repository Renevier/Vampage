#include "pch.h"
#include "Bonus.h"

void Bonus::InitShape()
{
	this->cShape.setRadius(10.f);
	this->cShape.setFillColor(Color::Red);
	this->cShape.setOrigin(Vector2f(this->cShape.getGlobalBounds().width / 2, this->cShape.getGlobalBounds().height / 2));
}

void Bonus::InitPosition(float _x, float _y)
{
	this->cShape.setPosition(Vector2f(_x, _y));
}

Bonus::Bonus(float _x, float _y)
{
	this->InitShape();
	this->InitPosition(_x, _y);
}

Bonus::~Bonus()
{
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
