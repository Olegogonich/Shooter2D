#pragma once
#include "GameObject.h"
#include "Controls.h"

struct Player : GameObject {

    const float jump_force = 10.f;
    const float top_speed = 5.f;
    const float acceleration = 1.f;
    const float friction = 0.6f;

    Controls* controls;

    Player(b2World*, const sf::Vector2f&, const sf::Vector2f&, Animator*, Controls*);

    void update() override;

    bool isOnFloor() const;

    void move();

    void jump();

    void stop();

    void shoot();

    void control();
};

