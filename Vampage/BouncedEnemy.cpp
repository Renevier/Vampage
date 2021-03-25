#include "pch.h"
#include "BouncedEnemy.h"

BouncedEnemy::BouncedEnemy(RenderWindow* _window, float _x, float _y, Player* _player)
	:Enemy(_window, _x, _y, _player)
{
	this->hp = 15;
	this->movementSpeed = 500.f;

	this->InitShape(Color::Cyan, Vector2f(120, 120));

	this->direction = this->player->GetPos() - this->shape.getPosition();
	this->normailizeDir.x = this->direction.x / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
	this->normailizeDir.y = this->direction.y / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));

	this->velocity = this->normailizeDir * this->movementSpeed;
}

void BouncedEnemy::Bounce()
{
	if (this->shape.getPosition().x <= 1 ||
		this->shape.getPosition().x >= this->window->getSize().x - 1)
		this->velocity.x = - this->velocity.x;
	else if (this->shape.getPosition().y <= 1 ||
		this->shape.getPosition().y >= this->window->getSize().y - 1)
		this->velocity.y = - this->velocity.y;
}

void BouncedEnemy::Move(const float& _dt)
{
	this->shape.move(velocity * _dt);
}

void BouncedEnemy::Update(const float& _dt)
{
	this->Move(_dt);
	this->Bounce();
}
