#pragma once
#include <vector>
#include <iostream>
#include "Bullet.h"
#include "Entity.h"
#include "Controls.h"
#include "Weapon.h"

#define JUMP_FORCE 2.5f
#define TOP_SPEED 1.0f
#define ACCELERATION 0.3f
#define FRICTION 0.6

struct Player : Entity {


    Controls* controls;

    Player(b2World&, const sf::Vector2f&, const sf::Vector2f&, const Animator&, const Controls&);

    void update() override;

    void control();

    ~Player();
};

