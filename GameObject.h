#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <iostream>

struct GameObject {

    sf::RectangleShape* shape;
    b2Body* body;

    GameObject(b2World* world, const b2BodyType& type, sf::Vector2f pos, sf::Vector2f size);

    virtual void update() const;

    void updateShapePosition() const;

    void updateShapeRotation() const;

    std::string toStringShapePosition() const;

    std::string toStringBodyPosition() const;

    ~GameObject();
};
