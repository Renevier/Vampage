#pragma once
#include "Entity.h"
class Bullet :
    public Entity
{
protected:
    CircleShape cShape;

    Vector2f mousePosition;

private:
    void InitShape(float _ray);
    void InitPos(float _x, float _y);

public:
    Bullet(Vector2f& _mousePosition, float _ray, float _x, float _y);
    ~Bullet();

    virtual void Move(const float& _dt);
    virtual void Update(const float& _dt);

    virtual void Draw(RenderTarget& _target);

    inline const CircleShape& GetShape() const { return this->cShape; }
    inline const Vector2f& GetDist() const { return this->direction; }
};

