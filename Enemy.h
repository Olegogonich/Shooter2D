#pragma once
#include <box2d.h>
#include <SFML/Graphics.hpp>
#include <random>
#include "Entity.h"

#define JUMP_FORCE 2.5f
#define TOP_SPEED 2.0f
#define ACCELERATION 0.3f
#define FRICTION 0.6f
#define RIGHT 1
#define LEFT 0

struct Enemy : Entity {

    float aiming_speed = 0.1;
    float attack_radius = 35;
    float range = 5;
    float chasing_range = 12.5;
    float min_angle_for_shooting = 0.5;
    bool direction = RIGHT;

    Enemy(b2World &, const sf::Vector2f &, const sf::Vector2f &, const Animator &);

    void update() override;

    void aim();

    void chase();

    void checkAmmo();

    void setTarget(Entity*);

    void resetTarget();

    ~Enemy();

private:
    Entity* target;

    b2Vec2 aimPos;
};
