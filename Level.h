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

    GameObject* createObject(const b2BodyType&, sf::Vector2f, sf::Vector2f, Animator*) const;

    Player* createPlayer(const b2BodyType&, sf::Vector2f, sf::Vector2f, Animator*) const;

    ~Level();
};
