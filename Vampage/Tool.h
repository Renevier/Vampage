#pragma once

const float pi(4.f * atan2f(1.f, 1.f));

enum class ENNEMIES_TYPE
{
	CaC,
	RANGE,
	BOUNCED,
	BOSS
};

enum class BONUS_EFFECT
{
	NONE,
	SHIELD,
	DASH_MAX,
	SHOOTING_DISTANCE
};

inline sf::RectangleShape rectangle(sf::Vector2f pos, sf::Vector2f size, sf::Color col = Color::Red, float ouT = 0, sf::Color ouC = Color::Transparent)
{
	sf::RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setFillColor(col);
	shape.setOutlineColor(ouC);
	shape.setOutlineThickness(ouT);

	return shape;
}