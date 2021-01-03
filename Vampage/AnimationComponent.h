#pragma once
#include "Animation.h"

class AnimationComponent
{
private:
	Texture& textureSheet;
	Sprite& sprite;
	map<string, Animation*> animations;

private:

public:
	AnimationComponent(Sprite& _sprite, Texture& _texture_sheet);
	~AnimationComponent();

	void AddAnimation(const string _key, float _animation_timer,
		int _start_frames_x, int _start_frames_y, int _frames_x, int _frames_y, int _width, int _height);

	void Play(const string _key, const float& _dt);
};

