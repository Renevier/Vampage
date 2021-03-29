#include "pch.h"
#include "Boss.h"

void Boss::InitRays()
{
	this->aimDir.push_back(rectangle(Vector2f(this->shape.getPosition().x + 200, this->shape.getPosition().y), Vector2f(10, 10)));
	this->aimDir.push_back(rectangle(Vector2f(this->shape.getPosition().x, this->shape.getPosition().y + 200), Vector2f(10, 10)));
}

Boss::Boss(RenderWindow* _window, float _x, float _y, Player* _player)
	:Enemy(_window, _x, _y, _player)
{
	this->hp = 50;

	this->InitShape(Color::Yellow, Vector2f(150, 150));
	this->InitPosition(_x, _y);
	this->InitRays();
	this->InitDeleteBullets();
}

void Boss::Shoot(const float& _dt)
{
	this->ray_1.push_back(make_shared<Bullet>(this->aimDir[0].getPosition(),
		this->shape.getPosition().x, this->shape.getPosition().y));
	
	this->ray_2.push_back(make_shared<Bullet>(this->aimDir[1].getPosition(),
		this->shape.getPosition().x, this->shape.getPosition().y));

	if (this->ray_1.size() != 0 &&
		this->ray_2.size() != 0)
	{
		for (auto& it : this->ray_1)
			it->Update(_dt);

		for (auto& it : this->ray_2)
			it->Update(_dt);
	}
	
	this->EraseBullets();
}

void Boss::EraseBullets() 
{
	if (this->ray_1.size() != 0 &&
		this->ray_2.size() != 0)
	{
		for (int i = 0; i < this->ray_1.size(); i++)
		{
			float distance = sqrt(
				pow(this->shape.getPosition().x - this->ray_1[i]->GetShape().getPosition().x, 2) +
				pow(this->shape.getPosition().y - this->ray_1[i]->GetShape().getPosition().y, 2)
			);

			if (distance >= this->deleteBullets.getRadius())
				this->ray_1.erase(this->ray_1.begin() + i);

			if (this->ray_1[i].get()->GetBounds().intersects(this->player->GetBounds()))
			{
				this->ray_1.erase(this->ray_1.begin() + i);
				this->player->ReceiveDamage(1);
			}
		}

		for (int i = 0; i < this->ray_2.size(); i++)
		{
			float distance = sqrt(
				pow(this->shape.getPosition().x - this->ray_2[i]->GetShape().getPosition().x, 2) +
				pow(this->shape.getPosition().y - this->ray_2[i]->GetShape().getPosition().y, 2)
			);

			if (distance >= this->deleteBullets.getRadius())
				this->ray_2.erase(this->ray_2.begin() + i);

			if (this->ray_1[i].get()->GetBounds().intersects(this->player->GetBounds()))
			{
				this->ray_1.erase(this->ray_1.begin() + i);
				this->player->ReceiveDamage(1);
			}
		}
	}
}

void Boss::Update(const float& _dt)
{
	this->UpdateRays(_dt);
	this->Shoot(_dt);
}

void Boss::UpdateRays(const float& _dt)
{
	this->rotation += _dt;
	rotation = fmod(this->rotation, 2 * pi);

	for (int i = 0; i < this->aimDir.size(); i++)
	{
		this->aimDir[i].setPosition(
			this->shape.getPosition().x + (200 * cos(2 * pi / this->aimDir.size() * i + this->rotation)),
			this->shape.getPosition().y + (200 * sin(2 * pi / this->aimDir.size() * i + this->rotation)));
	}
}

void Boss::Draw(RenderTarget& _target)
{
	/*for (auto it : this->aimDir)
		_target.draw(it);*/

	if (this->ray_1.size() != 0 &&
		this->ray_2.size() != 0)
	{
		for (auto& it : this->ray_1)
			it->Draw(_target);

		for (auto& it : this->ray_2)
			it->Draw(_target);
	}

	Enemy::Draw(_target);
}
