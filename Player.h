#pragma once
#include <vector>
#include <iostream>
#include "Bullet.h"
#include "PhysicalObject.h"
#include "Controls.h"
#include "Weapon.h"

struct Player : PhysicalObject {

    const float jump_force = 2.5f;
    const float top_speed = 1.f;
    const float acceleration = 0.3f;
    const float friction = 0.6f;

    float cannotShoot;
    Weapon* weapon;
    Controls* controls;

    Player(b2World&, const sf::Vector2f&, const sf::Vector2f&, const Animator&, const Controls&);

    void update() override;

    void setWeapon(const Weapon&);

    bool isOnFloor() const;

    bool shoot();

    void move();

    void jump();

    void stop();

    void control();

    ~Player();
};

