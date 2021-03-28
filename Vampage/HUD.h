#pragma once
#include "Player.h"

class HUD
{
private:
	RenderWindow* window;
	Texture lifeTexture;
	RectangleShape life;
	vector<RectangleShape> lifes;

	Player* player;

	void InitLifes(RenderWindow* _window);

public:
	HUD(Player* _player, RenderWindow* _window);
	~HUD() = default;

	void UpdateLifes();
	void Update();

	void Draw(RenderTarget& _target);
};