#include "Level.h"

Level::Level(const b2Vec2& gravity) : objects(new std::vector<GameObject*>), world(new b2World(gravity)) { }

GameObject* Level::createObject(const b2BodyType& type, sf::Vector2f pos, sf::Vector2f size, Animator* animator) const {
    auto* object = new GameObject(this->world, type, pos, size, animator);
    objects->push_back(object);
    return object;
}

Player * Level::createPlayer(sf::Vector2f pos, sf::Vector2f size, Animator* animator, Controls* controls) {
    auto* object = new Player(this->world, pos, size, animator, controls);
    objects->push_back(object);
    player = object;
    return object;
}

StaticObject *Level::createStatic(sf::Vector2f pos, sf::Vector2f size, sf::Texture *texture) const {
    auto* object = new StaticObject(this->world, pos, size, texture);
    objects->push_back(object);
    return object;
}

Level::~Level() {
    delete objects;
    delete world;
}
