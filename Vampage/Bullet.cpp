#include "pch.h"
#include "Bullet.h"

void Bullet::InitShape()
{
	this->shape.setSize(Vector2f(5.f, 5.f));
	this->shape.setFillColor(Color::Green);
	this->shape.setOrigin(Vector2f(this->shape.getGlobalBounds().width / 2,
		this->shape.getGlobalBounds().height / 2));
}

void Bullet::InitPos(float _x, float _y)
{
	this->shape.setPosition(_x, _y);
}

Bullet::Bullet(Vector2f _mousePosView, float _x, float _y)
{
	this->InitShape();
	this->InitPos(_x, _y);

	this->movementSpeed = 1000.f;

	this->mousePosView = _mousePosView; this->direction = this->mousePosView - this->shape.getPosition();
	this->normailizeDir.x = this->direction.x / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
	this->normailizeDir.y = this->direction.y / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
}

Bullet::~Bullet()
{
}

void Bullet::Move(const float& _dt)
{	this->velocity = this->normailizeDir * this->movementSpeed * _dt;

	this->shape.move(velocity);
}

void Bullet::Update(const float& _dt)
{
	this->Move(_dt);
}

void Bullet::Draw(RenderTarget& _target)
{
	_target.draw(this->shape);
}
