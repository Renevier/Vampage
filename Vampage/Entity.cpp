#include "pch.h"
#include "Entity.h"

void Entity::InitShape()
{
}

void Entity::InitPosition(float _x, float _y)
{
	this->shape.setPosition(_x, _y);
	this->shape.setOrigin(this->shape.getGlobalBounds().width / 2,
		this->shape.getGlobalBounds().height / 2);
}

Entity::Entity():
	movementSpeed(0.f), velocity(Vector2f(0, 0))
{
}

Entity::~Entity()
{
	
}