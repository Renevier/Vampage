#pragma once
#include "Entity.h"
#include "Tool.h"

class Bonus :
    public Entity
{
private:
    CircleShape cShape;
    BONUS_EFFECT effect;

    void InitShape();
    void InitPosition(float _x, float _y);

public:
    Bonus(float _x, float _y, BONUS_EFFECT _effect);
    ~Bonus() = default;

    virtual void Move(const float& _dt);
    virtual void Update(const float& _dt);
    virtual void Draw(RenderTarget& _target);

    inline const FloatRect& GetBounds() const { return this->cShape.getGlobalBounds(); }
    inline const BONUS_EFFECT& GetEffect() const { return this->effect; }
};