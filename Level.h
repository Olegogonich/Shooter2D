#pragma once
#include <SFML/Graphics.hpp>
#include "map"
#include <vector>
#include <box2d.h>
#include "PhysicalObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Vfx.h"

struct Level {

    const float n = 0.05;
    const float h = 0.45;
    const float r = 0.1;
    const float camera_offset_y = -200;

    sf::View* view;
    std::map<std::string, sf::Font*>* fonts;
    std::map<std::string, sf::Texture*>* textures;
    std::vector<Vfx*>* effects;
    Player* currentPlayer;
    std::vector<PhysicalObject*>* objects;
    std::vector<Bullet*>* bullets;
    std::vector<Entity*>* entities;
    std::vector<Player*>* players;
    std::vector<Enemy*>* enemies;
    b2World* world;
    sf::RenderWindow* window;

    Level(const b2Vec2&, sf::RenderWindow*);

    void update();

    PhysicalObject* createObject(const b2BodyType&, const sf::Vector2f&, const sf::Vector2f&, const Animator&) const;

    PhysicalObject* createStatic(const sf::Vector2f&, const sf::Vector2f&, const Animator&) const;

    PhysicalObject* createDynamic(const sf::Vector2f&, const sf::Vector2f&, const Animator&) const;

    Player* createPlayer(const sf::Vector2f&, const sf::Vector2f&, const Animator&, const Controls&);

    Enemy* createEnemy(const sf::Vector2f &, const sf::Vector2f &, const Animator &) const;

    Bullet* createBullet(const sf::Vector2f&, const sf::Vector2f&, const uint&, const float&, const float&, const float&, const Animator&) const;

    Vfx* createVfx(const Animation&, const sf::Vector2f&, const sf::Vector2f&, const float&, const bool&, const bool&) const;

    Weapon getPistol() const;

    void deleteBullet(Bullet*) const;

    void deleteEntity(Entity*) const;

    void deletePlayer(Player*) const;

    void deleteEnemy(Enemy*) const;

    void deleteVfx(Vfx*) const;

    void start();

    void stop();

    void gameover() const;

    sf::Font* loadFont(const std::string&, const std::string&) const;

    sf::Texture* loadTexture(const std::string&, const std::string&) const;

    ~Level();

private:

    static bool collide(PhysicalObject*, PhysicalObject*);

    void displayObjects() const;

    void displayEntities() const;

    void displayEffects() const;

    void displayText(const std::string&, const sf::Vector2u&, const uint&, const sf::Color&) const;

    void displayText(const std::string&, const sf::Vector2u&, const uint&, const sf::Color&, const sf::Color&, const float&) const;

    void displayText(sf::Text, const sf::Vector2u& pos) const;

    void loadDefaultFonts() const;

    void loadDefaultTextures() const;

    void movePlayerCamera() const;

    void displayEntityInfo(Entity*) const;

    void displayPlayerInfo() const;

    sf::Vector2f getMouseGlobalPosition() const;

    float getMouseToEntityAngle(Entity*) const;

    void checkShooting() const;

    void checkBullets() const;

    void checkDeaths();

    void checkEffects() const;

    void tellEnemiesPlayerPositions() const;

    void aimCurrentPlayer();
};
