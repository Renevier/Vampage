#pragma once
#include "GameState.h"
#include "MainMenuState.h"


class Game
{
private:
	RenderWindow* window;
	Event event;

	Clock clock;
	float deltaTime;

	stack<State*> states;


private:
	void InitWindow();
	void InitState();

public:
	Game();
	~Game();

	void Run();
	void Update();
	void UpdateEventSFML();
	void UpdateDt();
	void Render();
};
