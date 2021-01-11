#pragma once
#include "MovementComponent.h"
#include "HitBoxComponent.h"
#include "AnimationComponent.h"

class Entity
{
protected:
	RectangleShape shape;

	Vector2f position;
protected:
	virtual void InitShape() = 0;
	void InitPosition(float _x, float _y);
	
public:
	Entity();
	~Entity();

	virtual void Move();
	virtual void Update();
	virtual void Draw(RenderTarget& _target);
};

