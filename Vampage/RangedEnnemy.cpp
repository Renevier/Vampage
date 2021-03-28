#include "pch.h"
#include "RangedEnnemy.h"

RangedEnnemy::RangedEnnemy(RenderWindow* _window, float _x, float _y, Player* _player)
	:Enemy(_window, _x, _y, _player), timeBetweenShoot(0.f), shootingLenght(700.f)
{
	this->movementSpeed = 200.f;
	this->player = _player;
	this->window = _window;

	this->InitShape(Color::Red, Vector2f(70, 70));
}

void RangedEnnemy::Shoot(const float& _dt)
{
	this->timeBetweenShoot += _dt;

	if (this->timeBetweenShoot >= 1.f)
	{
		bullets.push_back(make_shared<Bullet>(this->player->GetPos(),
			this->shape.getPosition().x, this->shape.getPosition().y));

		this->timeBetweenShoot = 0;
	}

	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets[i]->Update(_dt);

		if (this->bullets[i]->GetShape().getGlobalBounds().intersects(this->player->GetBounds()))
		{
			this->bullets.erase(this->bullets.begin() + i);
			this->player->ReceiveDamage(1);
		}
		
		if (this->bullets[i]->GetShape().getPosition().x <= 0.f ||
			this->bullets[i]->GetShape().getPosition().x >= this->window->getSize().x ||
			this->bullets[i]->GetShape().getPosition().y >= this->window->getSize().y ||
			this->bullets[i]->GetShape().getPosition().y <= 0.f
			)
		{
			if (i != 0)
				i--;

			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void RangedEnnemy::Move(const float& _dt)
{
	if (this->shape.getGlobalBounds().intersects(this->player->GetNoSpawnArea().getGlobalBounds()))
		return;

	Enemy::Move(_dt);
}

void RangedEnnemy::Update(const float& _dt)
{
	Enemy::Update(_dt);

	this->Shoot(_dt);
}

void RangedEnnemy::Draw(RenderTarget& _target)
{
	Enemy::Draw(_target);

	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Draw(_target);
}
