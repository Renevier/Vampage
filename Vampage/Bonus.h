#pragma once
#include "Entity.h"
class Bonus :
    public Entity
{
private:
    CircleShape cShape;

    void InitShape();
    void InitPosition(float _x, float _y);

public:
    Bonus(float _x, float _y);
    ~Bonus();

    virtual void Move(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void Draw(RenderTarget& _target);
};

