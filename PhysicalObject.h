#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <iostream>
#include "Animator.h"
#include "Constants.h"

struct PhysicalObject {

    Animator* animator;
    sf::RectangleShape* shape;
    b2Body* body;
    sf::Vector2f position;
    sf::Vector2f size;

    PhysicalObject(b2World&, const b2BodyType&, sf::Vector2f, sf::Vector2f, const Animator&);

    PhysicalObject(b2World&, const b2BodyType&, sf::Vector2f, sf::Vector2f, sf::Texture*);

    virtual void update();

    void updateShapePosition() const;

    void updateShapeRotation() const;

    ~PhysicalObject();
};
