#pragma once
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"

class Enemy :
	public Entity
{
protected:
	CircleShape deleteBullets;
	RenderWindow* window;
	Player* player;

	int hp;

protected:
	void InitDeleteBullets();
	virtual void InitShape(Color _color, Vector2f _size);

public:
	Enemy(RenderWindow* _window, float _x, float _y, Player* _player);
	~Enemy() = default;

	void ReceiveDamage(int _damage);
	virtual void Move(const float& _dt);
	virtual void Update(const float& _dt);

	virtual void Draw(RenderTarget& _target);

	inline const RectangleShape& GetShape() const { return this->shape; }
	inline const int& GetHp() const { return this->hp; }
};

