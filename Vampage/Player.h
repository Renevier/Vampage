#pragma once
#include "Character.h"

class Player
	:public Character
{
private:

private:
	void InitComponent(float _x, float _y, Texture& _texture_sheet);

public:
	Player(float _x, float _y, Texture& _texture);
	~Player();


};

