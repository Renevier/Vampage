#pragma once

class State
{
protected:
	stack<State*>* states;
	RenderWindow* window;

	bool Quit;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	View view;

	map<string, Texture> textures;

protected:

public:
	State(RenderWindow* _window, stack<State*>* _states);
	~State() = default;

	virtual void UpdateMousePosition();
	virtual void UpdateInput(const float& _dt) = 0;
	virtual void Update(const float& _dt) = 0;
	virtual void Render(RenderTarget* _target) = 0;
	virtual void EndState() = 0;
	inline const bool& GetQuit() const { return this->Quit; }
};

