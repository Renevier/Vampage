#pragma once
class Animation
{
public:
	Texture& textureSheet;
	Sprite& sprite;
	IntRect startRect;
	IntRect currentRect;
	IntRect endRect;

	int width;
	int height;

	float animationTimer;
	float timer;

public:
	Animation(Sprite& _sprite, Texture& _texture_sheet, float _animation_timer,
		int _start_frames_x, int _start_frames_y, int _frames_x, int _frames_y, int _width, int _height);
	~Animation();

	void Update(const float& _dt);
	void Reset();
};

