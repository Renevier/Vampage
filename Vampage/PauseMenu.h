#pragma once
#include "Button.h"

class PauseMenu
{
	Font& font;
	Text menuText;

	RectangleShape background;
	RectangleShape buttonContainer;

	RectangleShape descriptionContainer;
	Text descriptionText;

	map<string, Button*> buttons;
private:
	void InitBackground(RenderWindow& window);
	void InitButtonContainer(RenderWindow& window);
	void InitText(Font& font);
	void InitDescriptionContainer(RenderWindow& window);
public:
	PauseMenu(RenderWindow& window, Font& _font);
	~PauseMenu();

	void Update(const Vector2i& mousePosWindow);
	void Render(RenderTarget& target, bool wantSave);
	void AddButton(const string key, float x, float y, const string text);
	bool IsButtonPressed(const string key);

	//get
	inline const map<string, Button*>& getButtons() { return this->buttons; };
};

