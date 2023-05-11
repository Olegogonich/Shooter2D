#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "GameObject.h"

struct Player : GameObject {

    const float jump_force = 10.f;
    const float walking_speed = 5.f;
    const float friction = 0.8f;
    const float air_speed = 0.5f;

    Player(b2World*, const b2BodyType&, const sf::Vector2f& , const sf::Vector2f&, Animator*);

    void update() const override;

    void jump(float height) const;

    void walk(float speed) const;

    void stop(float friction) const;

    void control() const;
};

