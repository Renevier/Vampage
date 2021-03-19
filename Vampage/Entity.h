#pragma once
#include "MovementComponent.h"
#include "HitBoxComponent.h"
#include "AnimationComponent.h"

class Entity
{
protected:
	RenderWindow* window;

	RectangleShape shape;
	float movementSpeed;

	Vector2f position;
	Vector2f velocity;

	Vector2f direction;
	Vector2f normailizeDir;
protected:
	virtual void InitShape();
	void InitPosition(float _x, float _y);
	
public:
	Entity();
	~Entity();

	virtual void Move(const float& _dt) = 0;
	virtual void Update(const float& _dt) = 0;
	virtual void Draw(RenderTarget& _target) = 0;

	inline const RectangleShape& GetShape() const { return this->shape; }
	inline const FloatRect& GetBounds() const { return this->shape.getGlobalBounds(); }
};

