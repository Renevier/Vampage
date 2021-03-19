#pragma once
#include "Enemy.h"

class RangedEnnemy: public Enemy
{
	float shootingLenght;
	float timeBetweenShoot;
	vector<shared_ptr<Bullet>> bullets;

public:
	RangedEnnemy(RenderWindow* _window, float _x, float _y, Player* _player);
	~RangedEnnemy() = default;

	void Shoot(const float& _dt);

	using Entity::Move;
	virtual void Move(const float& _dt);

	virtual void Update(const float& _dt);

	virtual void Draw(RenderTarget& _target);
};