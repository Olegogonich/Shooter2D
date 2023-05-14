#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Level.h"
#include "GameObject.h"
#include "renderer.h"
#include "Animator.h"
#include "Controls.h"


int main() {

    const b2Vec2 gravity(0.0f, 9.8f);
    const sf::Vector2u screen_size {1600, 1000};

    auto* window = new sf::RenderWindow();
    window->create(sf::VideoMode(screen_size.x, screen_size.y), "My window");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    auto* level = new Level(gravity);

    auto* playerAnimator = new Animator();
    auto* playerTextures = new std::vector<sf::Texture*>();

    std::string paths2[] = {
            "/Users/oleh/CLionProjects/Shooter2D/resources/images/man0.png",
            "/Users/oleh/CLionProjects/Shooter2D/resources/images/man1.png"
    };

    for (const std::string& path : paths2) {
        auto *texture = new sf::Texture();
        if (!texture->loadFromFile(path)) {
            std::cout << "file not found" << '\n';
        }
        texture->setSmooth(true);
        playerTextures->push_back(texture);
    }

    playerAnimator->createAnimation("running", playerTextures, 5);

    auto* textures1 = new std::vector<sf::Texture*>();

    std::string paths1[] = {
            "/Users/oleh/CLionProjects/Shooter2D/resources/images/man0.png",
    };

    for (const std::string& path : paths1) {
        auto *texture = new sf::Texture();
        if (!texture->loadFromFile(path)) {
            std::cout << "file not found" << '\n';
        }
        texture->setSmooth(true);
        textures1->push_back(texture);
    }

    playerAnimator->createAnimation("idle", textures1, 1);

    playerAnimator->currentAnimation = "idle";

    auto* controls = new Controls();

    std::vector<sf::Keyboard::Key> keys;
    keys.push_back(sf::Keyboard::Key::A);

    controls->addJumpKey(sf::Keyboard::Key::Space);
    controls->addJumpKey(sf::Keyboard::Key::Up);
    controls->addJumpKey(sf::Keyboard::Key::W);

    controls->addRightKey(sf::Keyboard::Key::Right);
    controls->addRightKey(sf::Keyboard::Key::D);

    controls->addLeftKey(sf::Keyboard::Key::Left);
    controls->addLeftKey(sf::Keyboard::Key::A);

    controls->setShootButton(sf::Mouse::Button::Left);

    auto* massData = new b2MassData();
    massData->mass = 1;

    level->createPlayer({10, 10}, {1, 2}, playerAnimator, controls);
    level->createStatic({-70, 25}, {200, 3}, playerTextures->at(0));
    level->createStatic({30, 17}, {4, 4}, playerTextures->at(0));
    level->createStatic({18, 18.5}, {1.2, 1}, playerTextures->at(1));
    level->createStatic({24, 17.25}, {1.2, 1}, playerTextures->at(1));
    level->createStatic({36, 20}, {1.2, 1}, playerTextures->at(1));
    level->createStatic({42, 16.5}, {1.2, 1}, playerTextures->at(1));

    render(window, level);

    delete textures1;
    delete playerTextures;
    delete controls;
    delete level;

    return 0;
}
