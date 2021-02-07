#pragma once
#include "MovementComponent.h"
#include "HitBoxComponent.h"
#include "AnimationComponent.h"

class Entity
{
protected:
	RectangleShape shape;
	float movementSpeed;

	Vector2f position;
	Vector2f velocity;

	Vector2f direction;
	Vector2f normailizeDir;
protected:
	virtual void InitShape() = 0;
	void InitPosition(float _x, float _y);
	
public:
	Entity();
	~Entity();

	virtual void Move(const float& _dt) = 0;
	virtual void Update(const float& _dt) = 0;
	virtual void Draw(RenderTarget& _target) = 0;
};

