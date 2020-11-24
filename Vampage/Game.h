#pragma once
#include "State.h"
#include "pch.h"

class Game
{
private:
	RenderWindow* window;
	Event event;

	Clock clock;
	float deltaTime;

	stack<State*> states;

	map<string, int> supportedKeys;

private:
	void InitWindow();
	void InitKeys();
	void InitState();

public:
	Game();
	void Run();
	void Update();
	void UpdateEventSFML();
	void UpdateDt();
	void Render();
	~Game();
};
