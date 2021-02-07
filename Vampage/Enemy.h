#pragma once
#include "Entity.h"
class Enemy :
	public Entity
{
protected:
	const Vector2f* playerPos;

protected:
	virtual void InitShape();

public:
	Enemy(float _x, float _y, const Vector2f* _playerPos);
	~Enemy();

	virtual void Move(const float& _dt);
	virtual void Update(const float& _dt);

	virtual void Draw(RenderTarget& _target);
};

