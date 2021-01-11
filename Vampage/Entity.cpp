#include "pch.h"
#include "Entity.h"

void Entity::InitPosition(float _x, float _y)
{
	this->shape.setPosition(_x, _y);
}

Entity::Entity()
{
}

Entity::~Entity()
{
	
}

void Entity::Move()
{
}

void Entity::Update()
{
}

void Entity::Draw(RenderTarget& _target)
{
	_target.draw(this->shape);
}

