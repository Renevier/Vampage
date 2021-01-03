#include "pch.h"
#include "Animation.h"

Animation::Animation(Sprite& _sprite, Texture& _texture_sheet, float _animation_timer, int _start_frames_x, int _start_frames_y, int _frames_x, int _frames_y, int _width, int _height)
	:sprite(_sprite), textureSheet(_texture_sheet), animationTimer(_animation_timer), width(_width), height(_height) 
{
	this->timer = 0;
	this->startRect = IntRect(_start_frames_x * width, _start_frames_y * height, width, height);
	this->currentRect = this->startRect;
	this->endRect = IntRect(_frames_x * width, _frames_y * height, width, height);

	this->sprite.setTexture(this->textureSheet);
	this->sprite.setTextureRect(this->startRect);
}

Animation::~Animation()
{
}

void Animation::Update(const float& _dt)
{
	//Update timer
	this->timer += 1000.f * _dt;

	if (this->timer >= this->animationTimer)
	{
		//reset timer
		this->timer = 0.f;

		//Animate
		if (this->currentRect != this->endRect)
		{
			this->currentRect.left += this->width;
		}
		//Reset
		else
		{
			this->currentRect.left = this->startRect.left;
		}

		this->sprite.setTextureRect(this->currentRect);
	}
}

void Animation::Reset()
{
	this->timer = 0.f;
	this->currentRect = this->startRect;

}
