#include "Button.h"

Button::Button(float _x, float _y, float _width, float _height, Font* _font, string _text, Color _idleColor, Color _hoverColor, Color _activeColor)
{
	this->buttonState = BTN_STATES::BTN_IDLE;

	this->shape.setSize(Vector2f(_width, _height));
	this->shape.setOrigin(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2);
	this->shape.setPosition(_x + this->shape.getGlobalBounds().width / 2,
		_y + this->shape.getGlobalBounds().height / 2);

	this->font = _font;

	this->text.setString(_text);
	this->text.setFont(*this->font);
	this->text.setCharacterSize(12);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
	this->text.setFillColor(Color::Black);

	this->idleColor = _idleColor;
	this->hoverColor = _hoverColor;
	this->activeColor = _activeColor;

	this->shape.setFillColor(this->idleColor);
}

void Button::Update(const Vector2f _mousePos)
{
	this->buttonState = BTN_STATES::BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(_mousePos))
	{
		if (this->shape.getGlobalBounds().contains(_mousePos))
		{
			this->buttonState = BTN_STATES::BTN_HOVER;

			if (Mouse::isButtonPressed(Mouse::Left))
				this->buttonState = BTN_STATES::BTN_PRESSED;
		}
	}

	switch (this->buttonState)
	{
	case BTN_STATES::BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_STATES::BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_STATES::BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(Color::Green);
		break;
	}
}

void Button::Render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

bool Button::IsPressed() const
{
	if (this->buttonState == BTN_STATES::BTN_PRESSED)
		return true;

	return false;
}

Button::~Button()
{
}