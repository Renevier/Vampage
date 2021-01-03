#pragma once
#include "MovementComponent.h"
#include "HitBoxComponent.h"
#include "AnimationComponent.h"

class Entity
{
protected:
	Sprite sprite;

	HitBoxComponent* hitBoxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

	Vector2f position;

protected:
	void VariableInit();
	void SetTexture(Texture& _texture);
	void CreateHitBoxComponent(Sprite& _sprite, float _offset_x, float _offset_y, float _width, float _height);
	void CreateMovementComponent(const float _maxVelocity, float _acceleration, float _deceleretion);
	void CreateAnimationComponent(Texture& _texture_sheet);

public:
	Entity();
	~Entity();

	virtual void Move(const float _x, const float _y, const float& _dt);
	virtual void Update(const float& _dt);
	virtual void Render(RenderTarget& _target);

	void StopVelocity();
	void StopVelocityX();
	void StopVelocityY();

	//get
	Vector2f GetPos();
	virtual Vector2i GetGridPosition(int _gridSizeU);
	FloatRect GetGlobalBounds();
	FloatRect GetNextPositionBounds(const float& _dt);

	//set
	inline void SetPosX(float pos) { this->position.x = pos; }
	inline void SetPosY(float pos) { this->position.y = pos; }
	virtual void SetPosition(const float _x, const float _y);

};

