#pragma once
#include "Character.h"

class Player
	:public Character
{
private:
	CircleShape noSpawnArea;

private:
	virtual void InitShape();
	void InitNoSpawnAera();

public:
	Player(float _x, float _y);
	~Player();

	void Draw(RenderTarget& _target);
};

