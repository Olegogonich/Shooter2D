#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <iostream>
#include "Animator.h"
#include "Constants.h"

struct GameObject {

    Animator* animator;
    sf::RectangleShape* shape;
    b2Body* body;

    GameObject(b2World*, const b2BodyType&, sf::Vector2f, sf::Vector2f, Animator*);

    virtual void update();

    void updateShapePosition() const;

    void updateShapeRotation() const;

    std::string toStringShapePosition() const;

    std::string toStringBodyPosition() const;

    ~GameObject();
};
