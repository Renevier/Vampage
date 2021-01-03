#include "pch.h"
#include "Entity.h"

void Entity::VariableInit()
{
	this->hitBoxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
}

void Entity::SetTexture(Texture& _texture)
{
	this->sprite.setTexture(_texture);
}

void Entity::CreateHitBoxComponent(Sprite& _sprite, float _offset_x, float _offset_y, float _width, float _height)
{
	this->hitBoxComponent = new HitBoxComponent(_sprite, _offset_x, _offset_y,
		_width, _height);
}

void Entity::CreateMovementComponent(const float _maxVelocity, float _acceleration, float _deceleretion)
{
	this->movementComponent = new MovementComponent(this->sprite, _maxVelocity, _acceleration, _deceleretion);
}

void Entity::CreateAnimationComponent(Texture& _texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, _texture_sheet);
}

Entity::Entity()
{
	this->VariableInit();
}

Entity::~Entity()
{
	delete this->hitBoxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
}

void Entity::SetPosition(const float _x, const float _y)
{
	if (this->hitBoxComponent)
		this->hitBoxComponent->SetPosition(_x, _y);
	else
		this->sprite.setPosition(_x, _y);
}

void Entity::Move(const float _dir_x, const float _dir_y, const float& _dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->Move(_dir_x, _dt);

		if (_dir_y < 0)
			this->position.x -= this->movementComponent->GetVelocity().x * _dt;
		if (_dir_y > 0)
			this->position.x += this->movementComponent->GetVelocity().x * _dt;
		if (_dir_x < 0)
			this->position.y -= this->movementComponent->GetVelocity().y * _dt;
		if (_dir_x > 0)
			this->position.y += this->movementComponent->GetVelocity().y * _dt;
	}
}

void Entity::Update(const float& _dt)
{

}

void Entity::Render(RenderTarget& _target)
{
	_target.draw(this->sprite);

	if (this->hitBoxComponent)
		this->hitBoxComponent->Render(_target);
}

void Entity::StopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->StopVelocity();
}

void Entity::StopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->StopVelocityX();
}

void Entity::StopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->StopVelocityY();
}


Vector2f Entity::GetPos()
{
	if (this->hitBoxComponent)
		return this->hitBoxComponent->GetPosition();

	return this->sprite.getPosition();
}

Vector2i Entity::GetGridPosition(int _gridSizeU)
{
	if (this->hitBoxComponent)
		return Vector2i(
			static_cast<int>(this->hitBoxComponent->GetPosition().x) / _gridSizeU,
			static_cast<int>(this->hitBoxComponent->GetPosition().y) / _gridSizeU);

	return Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / _gridSizeU,
		static_cast<int>(this->sprite.getPosition().y) / _gridSizeU);
}

FloatRect Entity::GetGlobalBounds()
{
	if (this->hitBoxComponent)
		return this->hitBoxComponent->GetGlobalBounds();

	return this->sprite.getGlobalBounds();
}

FloatRect Entity::GetNextPositionBounds(const float& _dt)
{
	if (this->hitBoxComponent && this->movementComponent)
		return this->hitBoxComponent->GetNextPosition(this->movementComponent->GetVelocity() * _dt);

	return FloatRect();
}
