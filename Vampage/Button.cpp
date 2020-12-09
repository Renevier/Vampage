#include "Button.h"

Button::Button(float _x, float _y, float _width, float _height,
	Font* _font, string _text, unsigned _charactere_size,
	Color _text_idle_color, Color _text_hover_color, Color _text_active_color,
	Color _button_idle_color, Color _button_hover_color, Color _button_active_color)
{
	this->buttonState = BTN_STATES::BTN_IDLE;

	this->shape.setSize(Vector2f(_width, _height));
	this->shape.setOrigin(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2);
	this->shape.setPosition(_x + this->shape.getGlobalBounds().width / 2,
		_y + this->shape.getGlobalBounds().height / 2);
	this->shape.setFillColor(_button_idle_color);

	this->font = _font;

	this->text.setString(_text);
	this->text.setFont(*this->font);
	this->text.setCharacterSize(_charactere_size);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
	this->text.setFillColor(_text_idle_color);

	this->textIdleColor = _text_idle_color;
	this->textHoverColor = _text_hover_color;
	this->textActiveColor = _text_active_color;

	this->buttonIdleColor = _button_idle_color;
	this->buttonHoverColor = _button_hover_color;
	this->buttonActiveColor = _button_active_color;

	this->shape.setFillColor(this->buttonIdleColor);
}

void Button::Update(const Vector2f& _mousePos)
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
		this->shape.setFillColor(this->buttonIdleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_STATES::BTN_HOVER:
		this->shape.setFillColor(this->buttonHoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_STATES::BTN_PRESSED:
		this->shape.setFillColor(this->buttonActiveColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(Color::Green);
		this->text.setFillColor(Color::Blue);
		break;
	}
}

void Button::Render(RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
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

BTN_STATES Button::GetState()
{
	return this->buttonState;
}
