#pragma once
#include "Button.h"

class Pause
{
private:
	Font font;
	RectangleShape bc;

	map<string, Button*> buttons;

	void InitBc(RenderWindow* _window);

public:
	Pause(RenderWindow* _window);
	~Pause() = default;

	void AddButtons(const string key, float x, float y, const string text);

	void Update(const Vector2f& _mousePos);

	void Draw(RenderTarget* _target);

	inline const map<string, Button*>& GetButtons() const { return this->buttons; }
};