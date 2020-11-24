#pragma once
#include "State.h"
#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
protected:
    Texture backgroundTexture;
    RectangleShape background;
    Font font;

    map<string, Button*> buttons;

private:
    virtual void InitKeybinds();
    void InitBackground();
    virtual void InitFont();
    void InitButton();

public:
    MainMenuState(RenderWindow* _window, map<string, int>* _supportedKeys, stack<State*>* _states);
    virtual void UpdateInput(const float& _dt);
    void UpdateButton();
    virtual void Update(const float& _dt);
    void RenderButton(RenderTarget* _target);
    virtual void Render(RenderTarget* _target);
    virtual void EndState();
    void CheckForQuit();
    ~MainMenuState();
};

