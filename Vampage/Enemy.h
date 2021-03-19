#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy :
	public Entity
{
protected:
	RenderWindow* window;
	Player* player;

protected:
	virtual void InitShape(Color _color, Vector2f _size);

public:
	Enemy(RenderWindow* _window, float _x, float _y, Player* _player);
	~Enemy() = default;

	virtual void Move(const float& _dt);
	virtual void Update(const float& _dt);

	virtual void Draw(RenderTarget& _target);

	inline const RectangleShape& GetShape() const { return this->shape; }
};

