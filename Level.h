#pragma once
#include <SFML/Graphics.hpp>
#include "map"
#include <vector>
#include <box2d.h>
#include "PhysicalObject.h"
#include "Player.h"
#include "StaticObject.h"
#include "Pistol.h"
#include "Bullet.h"

struct Level {
    sf::View* view;
    std::map<std::string, sf::Texture*>* textures;
    Player* player;
    std::vector<PhysicalObject*>* objects;
    std::vector<Bullet*>* bullets;
    std::vector<Entity*>* entities;
    b2World* world;
    sf::RenderWindow* window;

    Level(const b2Vec2&, sf::RenderWindow*);

    void update() const;

    PhysicalObject* createObject(const b2BodyType&, const sf::Vector2f&, const sf::Vector2f&, const Animator&) const;

    PhysicalObject* createObject(const b2BodyType&, const sf::Vector2f&, const sf::Vector2f&, sf::Texture*) const;

    Player* createPlayer(const sf::Vector2f&, const sf::Vector2f&, const Animator&, const Controls&);

    StaticObject* createStatic(const sf::Vector2f&, const sf::Vector2f&, sf::Texture*) const;

    Bullet* createBullet(const sf::Vector2f&, const sf::Vector2f&, const float&, const float&, sf::Texture*) const;

    Bullet* createBullet(const sf::Vector2f&, const sf::Vector2f&, const float&, const float&, const Animator&) const;

    sf::Texture* loadTexture(const std::string&, const std::string&) const;

    Weapon getPistol() const;

    void deleteBullet(Bullet*) const;

    static bool collide(PhysicalObject*, PhysicalObject*);

    void checkShooting() const;

    void checkBullets() const;

    ~Level();

private:
    void loadDefaultTextures() const;
};
