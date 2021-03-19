#pragma once
#include "Entity.h"
class Bullet :
    public Entity
{
protected:
    RenderWindow* window;
    Vector2f target;


private:
    void InitShape();
    void InitPos(float _x, float _y);

public:
    Bullet(Vector2f _target, float _x, float _y);
    ~Bullet();

    virtual void Move(const float& _dt);
    virtual void Update(const float& _dt);

    virtual void Draw(RenderTarget& _target);

    inline const RectangleShape& GetShape() const { return this->shape; }
    inline const FloatRect& GetBounds() const { return this->shape.getGlobalBounds(); }
};