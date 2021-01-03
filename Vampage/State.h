#pragma once

class State
{
protected:
	stack<State*>* states;
	RenderWindow* window;

	bool Quit;
	bool pause;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	View view;
	float viewSpeed;

	map<string, Texture> textures;

private:
	virtual void InitView();

public:
	State(RenderWindow* _window, stack<State*>* _states);
	virtual void UpdateMousePosition();
	virtual void UpdateInput(const float& _dt) = 0;
	virtual void Update(const float& _dt) = 0;
	virtual void Render(RenderTarget* _target) = 0;
	virtual void EndState() = 0;
	const bool& GetQuit() const;
	const bool& GetPause() const;
	~State();
};

