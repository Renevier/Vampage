#include "pch.h"
#include "Player.h"

void Player::InitComponent(float _x, float _y, Texture& _texture_sheet)
{
	this->position.x = _x;
	this->position.y = _y;

	this->SetPosition(this->position.x, this->position.y);

	this->CreateMovementComponent(300.f, 1500.f, 500.f);
	this->CreateAnimationComponent(_texture_sheet);
	this->CreateHitBoxComponent(this->sprite, -5.f, 0.f, 35.f, 35.f);
}

Player::Player(float _x, float _y, Texture& _texture)
{
}

Player::~Player()
{
}
