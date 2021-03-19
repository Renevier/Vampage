#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "Bonus.h"

class Player
	:public Entity
{
private:
	Texture playerTexture;
	CircleShape noSpawnArea;
	vector<shared_ptr<Bullet>> bullets;
	Vector2f* mousePosView;

	float shootingLenght;

	Clock clockDash;
	Time timeBetweenDash;

	int nbDashMax;
	int nbDash;

	float timeBetweenShoot { 0.f };
	vector<Bonus*> bonus;
		
private:
	virtual void InitShape();
	void InitNoSpawnAera();

public:
	Player(Vector2f* _mousePosView, float _x, float _y);
	~Player();

	void AddBonus(Bonus* _bonus);
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

	inline void SetNbDash(int _nbDash)
	{ 
		if (_nbDash > this->nbDashMax)
			_nbDash = this->nbDashMax;

		this->nbDash = _nbDash;
	}
};