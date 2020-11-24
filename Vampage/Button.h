#pragma once
#include "pch.h"

enum class BTN_STATES
{
	BTN_IDLE,
	BTN_HOVER,
	BTN_PRESSED
};

class Button
{
protected:
	BTN_STATES buttonState;

	RectangleShape shape;
	Font* font;
	Text text;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

private:

public:
	Button(float _x, float _y, float _width, float _height, Font* font, string text, Color _idleColor, Color _hoverColor, Color _activeColor);
	void Update(const Vector2f _mousePos);
	void Render(RenderTarget* target);
	bool IsPressed() const;
	~Button();


};
