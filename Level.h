#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <box2d.h>
#include "GameObject.h"
#include "Player.h"
#include "StaticObject.h"

struct Level {
    Player* player;
    std::vector<GameObject*>* objects;
    b2World* world;

    explicit Level(const b2Vec2& gravity);

    GameObject* createObject(const b2BodyType&, sf::Vector2f, sf::Vector2f, Animator*) const;

    Player * createPlayer(sf::Vector2f, sf::Vector2f, Animator*, Controls*);

    StaticObject* createStatic(sf::Vector2f, sf::Vector2f, sf::Texture*) const;

    ~Level();
};
