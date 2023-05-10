#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <box2d.h>
#include "GameObject.h"
#include "Player.h"

struct Level {
    std::vector<GameObject*>* objects;
    b2World* world;

    explicit Level(const b2Vec2& gravity);

    GameObject* createObject(const b2BodyType& type, sf::Vector2f pos, sf::Vector2f size) const;

    Player* createPlayer(const b2BodyType& type, sf::Vector2f pos, sf::Vector2f size) const;

    ~Level();
};
