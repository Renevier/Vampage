#include "pch.h"
#include "Enemy.h"

void Enemy::InitComponent(RenderWindow* _window)
{
	this->shape.setFillColor(Color::Green);

	this->shape.setPosition(
		static_cast<float>(rand() % static_cast<int>(_window->getSize().x - this->shape.getGlobalBounds().width)),
		0.f
	);

	this->shape.setSize(Vector2f(100.f, 100.f));
}

Enemy::Enemy(RenderWindow* _window)
{
	this->InitComponent(_window);
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

