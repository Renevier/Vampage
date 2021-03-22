#pragma once
#include "Bonus.h"

class LevelEnded
{
private:
	Font font;
	RectangleShape endLevel;

	Text endingLevelText;
	Text timerEndingLevel;
	Text score;

private:
	void InitShape(RenderWindow* _window);
	void InitText();
	void InitTimerText();
	void InitScore();

public:
	LevelEnded(RenderWindow* _window);
	~LevelEnded() = default;

	void UpdateTimer(const float& _timer);
	void UpdateScore(int _score);

	void Render(RenderTarget* _target);
};