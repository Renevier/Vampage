#pragma once
#include "State.h"
#include "Boss.h"

class BossState :
    public State
{
private:
    Player* player;
    unique_ptr<Boss> boss;

    void InitPlayer();
    void InitBoss();

public:
    BossState(RenderWindow* _window, stack<State*>* _states);
    ~BossState() = default;

    virtual void UpdateInput(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void Render(RenderTarget* _target);
    virtual void EndState();
};

