#include "pch.h"
#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(Sprite& _sprite, float _offset_x, float _offset_y, float _width, float _height)
	:sprite(_sprite), offsetX(_offset_x), offsetY(_offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = _width;
	this->nextPosition.height = _height;

	this->hitBox.setPosition(this->sprite.getPosition().x + _offset_x,
		this->sprite.getPosition().y + _offset_y);

	this->hitBox.setSize(Vector2f(_width, _height));
	this->hitBox.setFillColor(Color::Transparent);
	this->hitBox.setOutlineThickness(-1.f);
	this->hitBox.setOutlineColor(Color::Green);
}

HitBoxComponent::~HitBoxComponent()
{
}


bool HitBoxComponent::Intersect(const FloatRect& _frect)
{
	return this->hitBox.getGlobalBounds().intersects(_frect);
}

void HitBoxComponent::Update()
{
	this->hitBox.setPosition(this->sprite.getPosition().x + this->offsetX,
		this->sprite.getPosition().y + this->offsetY);
}

void HitBoxComponent::Render(RenderTarget& _target)
{
	_target.draw(this->hitBox);
}

FloatRect HitBoxComponent::GetNextPosition(const Vector2f& _velocity)
{
	this->nextPosition.left = this->hitBox.getPosition().x + _velocity.x;
	this->nextPosition.top = this->hitBox.getPosition().y + _velocity.y;

	return this->nextPosition;
}

void HitBoxComponent::SetPosition(Vector2f _position)
{
	this->hitBox.setPosition(_position);
	this->sprite.setPosition(_position.x - this->offsetX, _position.y - offsetY);
}

void HitBoxComponent::SetPosition(const float _x, const float _y)
{
	this->hitBox.setPosition(_x, _y);
	this->sprite.setPosition(_x - this->offsetX, _y - offsetY);
}