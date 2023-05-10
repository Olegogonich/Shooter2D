#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Level.h"
#include "GameObject.h"
#include "Player.h"
#include "renderer.h"


int main() {
    const b2Vec2 gravity(0.0f, 9.8f);
    const sf::Vector2u screen_size {1600, 1000};

    auto* window = new sf::RenderWindow();
    window->create(sf::VideoMode(screen_size.x, screen_size.y), "My window");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    sf::View view = window->getDefaultView();
    view.zoom(0.5f);

    auto* level = new Level(gravity);

    Player* player = level->createPlayer(b2_dynamicBody, {80.f, 20.f}, {3.f, 5.f});
    GameObject* obj1 = level->createObject(b2_staticBody, {80.f, 80.f}, {80.f, 10.f});
    GameObject* obj2 = level->createObject(b2_staticBody, {100.f, 60.f}, {40.f, 40.f});
    player->shape->setFillColor(sf::Color::Green);
    player->shape->setOutlineColor(sf::Color::Black);
    player->shape->setOutlineThickness(1.f);
    player->body->SetFixedRotation(true);
    obj1->shape->setFillColor(sf::Color::Black);

    render(window, level);

    delete level;

    return 0;
}
