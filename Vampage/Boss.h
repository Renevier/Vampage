#pragma once
#include "Enemy.h"

class Boss: public Enemy
{
private:
	
	vector<RectangleShape> aimDir;
	float rotation;

	vector<shared_ptr<Bullet>> ray_1;
	vector<shared_ptr<Bullet>> ray_2;

private:
	void InitRays();

public:
	Boss(RenderWindow* _window, float _x, float _y, Player* _player);
	~Boss() = default;

	void Shoot(const float& _dt);
	void EraseBullets();

	virtual void Update(const float& _dt);
	virtual void UpdateRays(const float& _dt);

	virtual void Draw(RenderTarget& _target);
};