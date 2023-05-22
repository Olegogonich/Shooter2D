#pragma once
#include "PhysicalObject.h"

struct Bullet : PhysicalObject {

    float power;
    float angle;
    uint damage;
    int lifetime;

    Bullet(b2World&, const sf::Vector2f&, const sf::Vector2f&, const uint&, const float&, const float&, const float&, const Animator&);

    void update() override;
};
