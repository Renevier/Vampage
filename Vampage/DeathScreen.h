#pragma once
#include "Button.h"

class DeathScreen
{
	Font font;
	RectangleShape bc;

	Text deathTxt;

	map<string, Button*> buttons;

	void InitBc(RenderWindow* _window);
	void InitText(RenderWindow* _window);

public:
	DeathScreen(RenderWindow* _window);
	~DeathScreen() = default;

	void AddButtons(const string key, float x, float y, const string text);

	void Update(const Vector2f & _mousePos);

	void Draw(RenderTarget * _target);

	inline const map<string, Button*>& GetButtons() const { return this->buttons; }
};

