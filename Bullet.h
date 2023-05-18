#pragma once
#include "PhysicalObject.h"

struct Bullet : PhysicalObject {

    float power;
    float angle;
    float lifetime;

    Bullet(b2World&, const sf::Vector2f&, const sf::Vector2f&, const float&, const float&, sf::Texture*);

    Bullet(b2World&, const sf::Vector2f&, const sf::Vector2f&, const float&, const float&, const Animator&);

    void update() override;
};
