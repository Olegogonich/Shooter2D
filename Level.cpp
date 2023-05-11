#include "Level.h"

Level::Level(const b2Vec2& gravity) : objects(new std::vector<GameObject*>), world(new b2World(gravity)) { }

GameObject* Level::createObject(const b2BodyType& type, sf::Vector2f pos, sf::Vector2f size, Animator* animator) const {
    auto* object = new GameObject(this->world, type, pos, size, animator);
    objects->push_back(object);
    return object;
}

Player* Level::createPlayer(const b2BodyType& type, sf::Vector2f pos, sf::Vector2f size, Animator* animator) const {
    auto* object = new Player(this->world, type, pos, size, animator);
    objects->push_back(object);
    return object;
}

Level::~Level() {
    delete objects;
    delete world;
}