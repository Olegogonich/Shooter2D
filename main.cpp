#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Level.h"
#include "GameObject.h"
#include "Player.h"
#include "renderer.h"
#include "Animator.h"


int main() {

    const b2Vec2 gravity(0.0f, 9.8f);
    const sf::Vector2u screen_size {1600, 1000};

    auto* window = new sf::RenderWindow();
    window->create(sf::VideoMode(screen_size.x, screen_size.y), "My window");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    sf::View view = window->getDefaultView();

    auto* level = new Level(gravity);

    auto* animator = new Animator();
    auto* textures = new std::vector<sf::Texture*>();

    std::string paths[] = {
            "/Users/oleh/CLionProjects/Shooter2D/resources/images/man0.png",
            "/Users/oleh/CLionProjects/Shooter2D/resources/images/man1.png"
    };

    for (const std::string& path : paths) {
        auto *texture = new sf::Texture();
        if (!texture->loadFromFile(path)) {
            std::cout << "file not found" << '\n';
        }
        texture->setSmooth(true);
        textures->push_back(texture);
    }

    animator->createAnimation("idle", textures, 5);
    animator->currentAnimationName = "idle";

    level->createObject(b2_dynamicBody, {0, 0}, {10, 10}, animator);

    render(window, level);

    delete textures;
    delete level;

    return 0;
}
