#pragma once
#include "PhysicalObject.h"
#include "Weapon.h"
#include "Animator.h"

struct Entity : PhysicalObject {

    float jump_force;
    float top_speed;
    float acceleration;
    float friction;

    bool shooting;
    bool reloading;
    uint health;

    float cannotShoot;
    Weapon* weapon;

    Entity(b2World&, const sf::Vector2f&, const sf::Vector2f&, const Animator&, const uint&, const float&, const float&, const float&, const float&);

    void update() override;

    void setWeapon(const Weapon&);

    bool isOnFloor() const;

    void jump();

    void moveRight();

    void moveLeft();

    void stop();

    void shoot();

    void reload();

    void dealDamage(const uint&);

    ~Entity();
};
