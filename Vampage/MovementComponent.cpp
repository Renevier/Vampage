#include "pch.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(Sprite& _sprite, float _maxVelocity, float _acceleration, float _deceleretion)
	:sprite(_sprite), maxVelocity(_maxVelocity), acceleration(_acceleration), deceleration(_deceleretion)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Move(const float _dir_x, const float& _dt)
{
	//Acceleration
	this->velocity.x += this->acceleration * _dir_x * _dt;
}

void MovementComponent::Update(const float& _dt)
{
	if (velocity.x > 0)
	{
		//Max velocity check positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration x positive
		this->velocity.x -= this->deceleration * _dt;
		if (velocity.x < 0)
			this->velocity.x = 0;

	}
	else if (velocity.x < 0)
	{
		//Max velocity check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration x negative
		this->velocity.x += this->deceleration * _dt;
		if (velocity.x > 0)
			this->velocity.x = 0;
	}

	//Final move
	this->sprite.move(this->velocity * _dt);
}

bool MovementComponent::isIdle()
{
	if (this->velocity.x == 0.f && this->velocity.y == 0)
		return true;

	return false;
}

bool MovementComponent::isMovingLeft()
{
	if (this->velocity.x < 0.f)
		return true;

	return false;
}

bool MovementComponent::isMovingRight()
{
	if (this->velocity.x > 0.f)
		return true;

	return false;
}
