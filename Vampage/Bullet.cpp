#include "pch.h"
#include "Bullet.h"

void Bullet::InitShape(float _ray)
{
	this->cShape.setRadius(_ray);
	this->cShape.setFillColor(Color::Green);
	this->cShape.setOrigin(Vector2f(this->cShape.getGlobalBounds().width / 2,
		this->cShape.getGlobalBounds().height / 2));
}

void Bullet::InitPos(float _x, float _y)
{
	this->cShape.setPosition(_x, _y);
}

Bullet::Bullet(Vector2f _mousePosView, float _ray, float _x, float _y)
{
	this->InitShape(_ray);
	this->InitPos(_x, _y);

	this->movementSpeed = 1000.f;

	this->mousePosView = _mousePosView; this->direction = this->mousePosView - this->cShape.getPosition();
	this->normailizeDir = this->direction / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
}

Bullet::~Bullet()
{
}

void Bullet::Move(const float& _dt)
{	this->velocity = this->normailizeDir * this->movementSpeed * _dt;

	this->cShape.move(velocity);
}

void Bullet::Update(const float& _dt)
{
	this->Move(_dt);
}

void Bullet::Draw(RenderTarget& _target)
{
	_target.draw(this->cShape);
}
