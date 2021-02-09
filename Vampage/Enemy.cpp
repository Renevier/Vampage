#include "pch.h"
#include "Enemy.h"

void Enemy::InitShape()
{
	this->shape.setFillColor(Color::Green);
	this->shape.setSize(Vector2f(100.f, 100.f));
}

Enemy::Enemy(float _x, float _y, const Vector2f* _playerPos)
{
	this->InitShape();
	this->InitPosition(_x, _y);

	this->playerPos = _playerPos;
	this->movementSpeed = 550.f;
}

Enemy::~Enemy()
{
}

void Enemy::Move(const float& _dt)
{
	this->direction = *this->playerPos - this->shape.getPosition();

	this->normailizeDir.x = this->direction.x / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
	this->normailizeDir.y = this->direction.y / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));

	this->velocity = this->normailizeDir * this->movementSpeed * _dt;

	this->shape.move(velocity);
}

void Enemy::Update(const float& _dt)
{
	this->Move(_dt);
}

void Enemy::Draw(RenderTarget& _target)
{
	_target.draw(this->shape);
}
