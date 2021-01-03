#pragma once
#include "State.h"
#include "Player.h"
class GameState :
    public State
{
private:
    View view;
    RenderTexture renderTexture;
    Sprite renderSprite;

    Player* player;

private:
    void InitTexture();
    void InitPlayer();

public:
    GameState(RenderWindow* _window, stack<State*>* _states);
    virtual void UpdateInput(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void Render(RenderTarget* _target);
    void UpdateState();
    virtual void EndState();
    void CheckForPause();
    void PauseMenu();
    ~GameState();
};

