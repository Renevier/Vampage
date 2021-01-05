#pragma once
#include "Character.h"
class Enemy:
    public Character
{
protected:
    RectangleShape shape;

protected:
    void InitComponent();

public:
    Enemy();
    ~Enemy();

    void Move(float _x, float _y);
    void Update();
    void Draw(RenderTarget& _target);

    //Set

    inline void SetFillColor(Color _color) { this->shape.setFillColor(_color); }
};

