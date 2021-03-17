#include "pch.h"
#include "LevelEnded.h"

void LevelEnded::InitShape(RenderWindow* _window)
{
	this->endLevel.setSize(Vector2f(500, _window->getSize().y));
	this->endLevel.setFillColor(Color(20, 20, 20, 200));
	this->endLevel.setOutlineColor(Color::Red);
	this->endLevel.setOutlineThickness(1.f);

	this->endLevel.setOrigin(Vector2f(
		this->endLevel.getGlobalBounds().width / 2,
		this->endLevel.getGlobalBounds().height / 2
	));

	this->endLevel.setPosition(Vector2f(
		_window->getSize().x / 2,
		_window->getSize().y / 2
	));
}

void LevelEnded::InitText()
{
	if (!this->font.loadFromFile("../Resources/Fonts/SteampunkMachineryFont-Regular.ttf"))
		exit(0);

	this->endingLevelText.setFont(this->font);
	this->endingLevelText.setFillColor(Color::Red);
	this->endingLevelText.setCharacterSize(60);
	this->endingLevelText.setString("LEVEL DONE ! \n \n WAVE CLEAR");
	this->endingLevelText.setOrigin(Vector2f(
		this->endingLevelText.getGlobalBounds().width / 2,
		this->endingLevelText.getGlobalBounds().height / 2
	));

	this->endingLevelText.setPosition(Vector2f(
		this->endLevel.getPosition().x, 
		this->endLevel.getPosition().y - this->endLevel.getGlobalBounds().height / 2 + this->endingLevelText.getGlobalBounds().height
	));

	
}

void LevelEnded::InitTimerText()
{
	this->timerEndingLevel.setFont(this->font);
	this->timerEndingLevel.setFillColor(Color::Red);
	this->timerEndingLevel.setCharacterSize(60);
	this->timerEndingLevel.setString("5");

	this->timerEndingLevel.setOrigin(Vector2f(
		this->timerEndingLevel.getGlobalBounds().width / 2,
		this->timerEndingLevel.getGlobalBounds().height / 2
	));

	this->timerEndingLevel.setPosition(Vector2f(
		this->endLevel.getPosition().x,
		this->endLevel.getPosition().y + this->endLevel.getGlobalBounds().height / 2 - this->timerEndingLevel.getGlobalBounds().height
	));
}

void LevelEnded::InitScore()
{
	this->score.setFont(this->font);
	this->score.setFillColor(Color::Red);
	this->score.setCharacterSize(60);
	this->score.setString("SCORE \n 0");

	this->score.setOrigin(Vector2f(
		this->score.getGlobalBounds().width / 2,
		this->score.getGlobalBounds().height / 2
	));

	this->score.setPosition(Vector2f(
		this->endLevel.getPosition().x,
		this->endLevel.getPosition().y
	));
}

LevelEnded::LevelEnded(RenderWindow* _window)
{
	this->InitShape(_window);
	this->InitText();
	this->InitTimerText();
	this->InitScore();
}

void LevelEnded::UpdateTimer(const float& _timer)
{
	int timer = 5 - _timer;

	this->timerEndingLevel.setString("NEXT WAVE IN\n\t " + to_string(timer));
									 
	this->timerEndingLevel.setOrigin(Vector2f(
		this->timerEndingLevel.getGlobalBounds().width / 2,
		this->timerEndingLevel.getGlobalBounds().height / 2
	));

	this->timerEndingLevel.setPosition(Vector2f(
		this->endLevel.getPosition().x,
		this->endLevel.getPosition().y + this->endLevel.getGlobalBounds().height / 2 - this->timerEndingLevel.getGlobalBounds().height
	));
}

void LevelEnded::UpdateScore(int _score)
{
	this->score.setString("SCORE \n " + to_string(_score));
}

void LevelEnded::Render(RenderTarget* _target)
{
	_target->draw(this->endLevel);
	_target->draw(this->endingLevelText);
	_target->draw(this->timerEndingLevel);
	_target->draw(this->score);
}
