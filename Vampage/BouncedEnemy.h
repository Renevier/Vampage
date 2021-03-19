#pragma once
#include "Enemy.h"
class BouncedEnemy :
    public Enemy
{
public:
    BouncedEnemy(RenderWindow* _window, float _x, float _y, Player* _player);
    ~BouncedEnemy() = default;

    void Bounce();

    virtual void Move(const float& _dt);

    virtual void Update(const float& _dt);
};

