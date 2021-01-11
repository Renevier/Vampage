#pragma once
#include "Character.h"
class Enemy:
    public Character
{
protected:

protected:
    virtual void InitShape();

public:
    Enemy(float _x, float _y);
    ~Enemy();
};

