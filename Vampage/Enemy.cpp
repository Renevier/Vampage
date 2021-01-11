#include "pch.h"
#include "Enemy.h"

void Enemy::InitShape()
{
	this->shape.setFillColor(Color::Green);

	this->shape.setSize(Vector2f(100.f, 100.f));
}

Enemy::Enemy(float _x, float _y)
{
	this->InitShape();
	this->InitPosition(_x, _y);
}

Enemy::~Enemy()
{
}