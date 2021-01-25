#pragma once
#include "Character.h"

class Player
	:public Character
{
private:
	CircleShape noSpawnArea;
	Vertex line[2];

private:
	virtual void InitShape();
	void InitNoSpawnAera();
	void InitRayCast();

public:
	Player(float _x, float _y);
	~Player();

	void Draw(RenderTarget& _target);

	inline CircleShape GetNoSpawnArea() { return this->noSpawnArea; }
};