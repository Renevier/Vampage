#pragma once
#include "Entity.h"
#include "Bullet.h"

class Player
	:public Entity
{
private:
	CircleShape noSpawnArea;
	vector<shared_ptr<Bullet>> bullets;
	Vector2f* mousePosView;

	float shootingLenght;

	Clock clockDash;
	Time timeBeetweenDash;

	int nbDash;

	float timeBetweenShoot { 0.f };

	unsigned int nbEnnemie{ 0 };
	
private:
	virtual void InitShape();
	void InitNoSpawnAera();

public:
	Player(Vector2f* _mousePosView, float _x, float _y);
	~Player() = default;

	virtual void Move(const float& _dt);
	void Dash(const float& _dt);
	void Shoot(const float& _dt);
	void UpdateNoSpawnArea();
	virtual void Update(const float& _dt);

	void RenderBullets(RenderTarget& _target);
	virtual void Draw(RenderTarget& _target);

	inline CircleShape& GetNoSpawnArea() { return this->noSpawnArea; }
	inline const Vector2f& GetPos() const { return this->shape.getPosition(); }
	inline vector<shared_ptr<Bullet>>& GetBullets() { return this->bullets; }
};