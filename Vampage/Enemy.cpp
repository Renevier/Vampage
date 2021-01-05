#include "pch.h"
#include "Enemy.h"

void Enemy::InitComponent()
{
	//this->shape.setPosition(10.f, 10.f);
	this->shape.setSize(Vector2f(100.f, 100.f));
	this->shape.setFillColor(Color::Cyan);
	this->shape.setOutlineColor(Color::Green);
	this->shape.setOutlineThickness(1.f);
}

Enemy::Enemy()
{
	this->InitComponent();
}

Enemy::~Enemy()
{
}

void Enemy::Move(float _x, float _y)
{
	this->shape.move(_x, _y);
}

void Enemy::Update()
{
}

void Enemy::Draw(RenderTarget& _target)
{
	_target.draw(this->shape);
}

