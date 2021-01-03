#pragma once
class HitBoxComponent
{
protected:
	Sprite& sprite;
	RectangleShape hitBox;
	FloatRect nextPosition;

	float offsetX;
	float offsetY;

public:
	HitBoxComponent(Sprite& _sprite, float _offset_x, float _offset_y, float _width, float _height);
	~HitBoxComponent();

	bool Intersect(const FloatRect& _frect);
	void Update();
	void Render(RenderTarget& _target);

	//Get
	inline Vector2f GetPosition() { return this->hitBox.getPosition(); }
	inline FloatRect GetGlobalBounds() { return this->hitBox.getGlobalBounds(); }
	FloatRect GetNextPosition(const Vector2f& _velocity);

	//Set
	void SetPosition(Vector2f _position);
	void SetPosition(const float _x, const float _y);
};

