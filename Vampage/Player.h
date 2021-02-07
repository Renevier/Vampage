#pragma once
#include "Entity.h"

class Player
	:public Entity
{
private:
	CircleShape noSpawnArea;

private:
	virtual void InitShape();
	void InitNoSpawnAera();

public:
	Player(float _x, float _y);
	~Player();

	virtual void Move(const float& _dt);

	virtual void Update(const float& _dt);
	void UpdateNoSpawnArea();

	virtual void Draw(RenderTarget& _target);

	inline CircleShape& GetNoSpawnArea() { return this->noSpawnArea; }
	inline const Vector2f& GetPos() const { return this->shape.getPosition(); }
};