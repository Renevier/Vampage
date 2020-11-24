#pragma once
#include "State.h"
class GameState :
    public State
{
private:
    virtual void InitKeybinds();

public:
    GameState(RenderWindow* _window, map<string, int>* _supportedKeys, stack<State*>* _states);
    virtual void UpdateInput(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void Render(RenderTarget* _target);
    void UpdateState();
    virtual void EndState();
    void CheckForPause();
    void PauseMenu();
    ~GameState();
};

