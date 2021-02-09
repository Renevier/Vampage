#pragma once
#include "Entity.h"
#include "Bullet.h"

class Player
	:public Entity
{
private:
	CircleShape noSpawnArea;

	vector<unique_ptr<Bullet>> bullets;

	Vector2f mousePosView;

private:
	virtual void InitShape();
	void InitNoSpawnAera();

public:
	Player(float _x, float _y, Vector2f _mousePosView);
	~Player();

	virtual void Move(const float& _dt);
	void Shoot(const float& _dt);
	void UpdateNoSpawnArea();
	virtual void Update(const float& _dt);

	void RenderBullets(RenderTarget& _target);
	virtual void Draw(RenderTarget& _target);

	inline CircleShape& GetNoSpawnArea() { return this->noSpawnArea; }
	inline const Vector2f& GetPos() const { return this->shape.getPosition(); }
};