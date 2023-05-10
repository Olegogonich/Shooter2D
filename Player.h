#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "GameObject.h"

struct Player : GameObject {

    const float jump_force = 5.f;
    const float walking_speed = 2.f;
    const float acceleration = 0.1f;

    Player(b2World *world, const b2BodyType &type, const sf::Vector2f& pos, const sf::Vector2f& size);

    void update() const override;

    void jump(float height) const;

    void walk(float speed) const;

    void accelerate(float acceleration);

    void stop(float friction) const;

    void control() const;
};

