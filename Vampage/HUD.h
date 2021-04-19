#pragma once
#include "Player.h"

class HUD
{
private:
	RenderWindow* window;

	Texture dashTexture;
	RectangleShape dash;
	vector<RectangleShape> dashes;

	Texture lifeTexture;
	RectangleShape life;
	vector<RectangleShape> lifes;

	Font font;
	Text textLevel;

	Player* player;

	void InitLifes();
	void InitDashes();
	void InitTextLevel();

public:
	HUD(Player* _player, RenderWindow* _window);
	~HUD() = default;

	void UpdateLifes();
	void UpdateDashes();
	void UpdateTextLevel(int _lvl);
	void Update(int _lvl);

	void Draw(RenderTarget& _target);
};