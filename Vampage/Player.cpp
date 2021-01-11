#include "pch.h"
#include "Player.h"

void Player::InitShape()
{
	this->shape.setSize(Vector2f(50, 50));
	this->shape.setFillColor(Color::Blue);
	this->shape.setOrigin(Vector2f(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2));
}

void Player::InitNoSpawnAera()
{
	this->noSpawnArea.setPosition(this->shape.getOrigin());
	this->noSpawnArea.setRadius(10.f);
	this->noSpawnArea.setFillColor(Color::Transparent);
	this->noSpawnArea.setOutlineThickness(1.f);
	this->noSpawnArea.setOutlineColor(Color::Green);
}

Player::Player(float _x, float _y)
{
	this->InitShape();
	this->InitPosition(_x, _y);
	this->InitNoSpawnAera();
}

Player::~Player()
{
}

void Player::Draw(RenderTarget& _target)
{
	Entity::Draw(_target);

	_target.draw(this->noSpawnArea);
}
