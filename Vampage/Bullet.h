#pragma once
#include "Entity.h"
class Bullet :
    public Entity
{
protected:
    RenderWindow* window;
    Vector2f mousePosView;


private:
    void InitShape();
    void InitPos(float _x, float _y);

public:
    Bullet(Vector2f _mousePosView, float _x, float _y);
    ~Bullet();

    virtual void Move(const float& _dt);
    virtual void Update(const float& _dt);

    virtual void Draw(RenderTarget& _target);

    inline const RectangleShape& GetShape() const { return this->shape; }
};