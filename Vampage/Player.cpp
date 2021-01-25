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
	this->noSpawnArea.setRadius(200.f);
	this->noSpawnArea.setOrigin(this->noSpawnArea.getRadius(), this->noSpawnArea.getRadius());
	this->noSpawnArea.setFillColor(Color::Transparent);
	this->noSpawnArea.setPosition(this->shape.getPosition());

	this->noSpawnArea.setOutlineThickness(1.f);
	this->noSpawnArea.setOutlineColor(Color::Green);
}

void Player::InitRayCast()
{
	this->line[0].position = Vector2f(this->shape.getPosition().x, this->shape.getPosition().y);
	this->line[0].color = Color::Red;
	this->line[1].position = Vector2f(this->shape.getPosition().x + 50, this->shape.getPosition().y);
	this->line[1].color = Color::Red;
}

Player::Player(float _x, float _y)
{
	this->InitShape();
	this->InitPosition(_x, _y);
	this->InitNoSpawnAera();
	this->InitRayCast();
}

Player::~Player()
{
}

void Player::Draw(RenderTarget& _target)
{
	Entity::Draw(_target);

	_target.draw(this->noSpawnArea);
	_target.draw(this->line, 2, Lines);

}
