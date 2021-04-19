#include "pch.h"
#include "Enemy.h"

void Enemy::InitDeleteBullets()
{
	this->deleteBullets.setRadius(800.f);
	this->deleteBullets.setOrigin(
		this->deleteBullets.getRadius(),
		this->deleteBullets.getRadius()
	);

	this->deleteBullets.setFillColor(Color::Transparent);
	this->deleteBullets.setPosition(this->shape.getPosition());

	this->deleteBullets.setOutlineThickness(1.f);
	this->deleteBullets.setOutlineColor(Color::Yellow);
}

void Enemy::InitShape(Color _color, Vector2f _size)
{
	this->shape.setFillColor(_color);
	this->shape.setSize(_size);
}

Enemy::Enemy(RenderWindow* _window, float _x, float _y, Player* _player)
	:window(_window), player(_player), hp(1)
{
	this->movementSpeed = 400.f;

	this->InitShape(Color::Green, Vector2f(50, 50));
	this->InitPosition(_x, _y);

}

void Enemy::ReceiveDamage(int _damage)
{
	this->hp -= _damage;
}

void Enemy::DealDamage()
{
	if (this->shape.getGlobalBounds().intersects(this->player->GetBounds()))
	{
		if (!this->player->GetInvu())
		{
			if(this->player->GetShield())
			{
				this->player->SetShield(false);
				this->player->SetInvu(true);
			}
			else
			{
				this->player->ReceiveDamage(1);
				this->player->SetInvu(true);
			}
		}
	}
}

void Enemy::Move(const float& _dt)
{
	this->direction = this->player->GetPos() - this->shape.getPosition();

	this->normailizeDir.x = this->direction.x / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
	this->normailizeDir.y = this->direction.y / sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));

	this->velocity = this->normailizeDir * this->movementSpeed * _dt;

	this->shape.move(velocity);
}

void Enemy::Update(const float& _dt)
{
	this->deleteBullets.setPosition(this->shape.getPosition());
	this->Move(_dt);
	this->DealDamage();
}

void Enemy::Draw(RenderTarget& _target)
{
	_target.draw(this->shape);
	//_target.draw(this->deleteBullets);
}
