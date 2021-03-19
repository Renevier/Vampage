#include "pch.h"
#include "Enemy.h"

void Enemy::InitShape(Color _color, Vector2f _size)
{
	this->shape.setFillColor(_color);
	this->shape.setSize(_size);
}

Enemy::Enemy(RenderWindow* _window, float _x, float _y, Player* _player)
{
	this->InitShape(Color::Green, Vector2f(50, 50));
	this->InitPosition(_x, _y);

	this->player = _player;
	this->movementSpeed = 400.f;
	this->window = _window;
}

void Enemy::Move(const float& _dt)
{
	this->direction = this->player->GetPos() - this->shape.getPosition();

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
