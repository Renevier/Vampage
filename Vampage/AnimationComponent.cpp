#include "pch.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& _sprite, Texture& _texture_sheet)
	:sprite(_sprite), textureSheet(_texture_sheet)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::AddAnimation(const string _key,
	float _animation_timer,
	int _start_frames_x, int _start_frames_y, int _frames_x, int _frames_y, int _width, int _height)
{
	this->animations[_key] = new Animation(
		this->sprite, this->textureSheet,
		_animation_timer,
		_start_frames_x, _start_frames_y, _frames_x, _frames_y, _width, _height);
}

void AnimationComponent::Play(const string _key, const float& _dt)
{
	this->animations[_key]->Update(_dt);
}