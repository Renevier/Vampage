#pragma once
#include "Character.h"
class Enemy:
    public Character
{
protected:
    RectangleShape shape;

protected:
    void InitComponent(RenderWindow* _window);

public:
    Enemy(RenderWindow* _window);
    ~Enemy();

    void Move(float _x, float _y);
    void Update();
    void Draw(RenderTarget& _target);

    //Set
    inline Vector2f GetPosition() { return this->shape.getPosition(); }
};

