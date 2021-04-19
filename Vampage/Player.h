#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "Bonus.h"

class Player
	:public Entity
{
private:
	enum class DIRECTION
	{
		NONE,
		UP,
		LEFT,
		RIGHT,
		DOWN
	};

	DIRECTION dir{ DIRECTION::NONE };

	Texture playerTexture;
	CircleShape noSpawnArea;
	CircleShape shield;
	vector<shared_ptr<Bullet>> bullets;
	Vector2f* mousePosView;
	unsigned int lifePoint{ 3 };
	bool isInvu{ false };
	float timerInvu{ 0.f };

	float timeBetweenDash;
	float dashRecover{ 0.f };
	bool dash{ false };
	int nbDashMax;
	int nbDash;

	float timeBetweenShoot { 0.f };
	vector<Bonus*> bonus;
	bool haveShield{ false };
	bool gainHP{ false };
		
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
	void CheckBonus();
	virtual void Update(const float& _dt);

	void RenderBullets(RenderTarget& _target);
	virtual void Draw(RenderTarget& _target);

	inline CircleShape& GetNoSpawnArea() { return this->noSpawnArea; }
	inline const Vector2f& GetPos() const { return this->shape.getPosition(); }
	inline vector<shared_ptr<Bullet>>& GetBullets() { return this->bullets; }
	inline bool& GetInvu() { return this->isInvu; }
	inline unsigned int& GetHP() { return this->lifePoint; }
	inline int& GetNbDash() { return this->nbDash; }
	inline bool& GetShield() { return this->haveShield; }

	inline void SetNbDash() { this->nbDash = this->nbDashMax; }
	inline void ReceiveDamage(int _damage) { this->lifePoint -= _damage; }
	inline void SetInvu(bool _isInvu) { this->isInvu = _isInvu;	}
	inline void SetShield(bool _haveShield) { this->haveShield = _haveShield;	}
	inline void SetGainHp(bool _gainHp) { this->gainHP = _gainHp;	}
};