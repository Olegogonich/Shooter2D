#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "Level.h"
#include "renderer.h"
#include "Animator.h"
#include "Controls.h"
#include "Weapon.h"
#include "Pistol.h"

Controls getDefaultControls() {
    Controls controls;

    controls.addJumpKey(sf::Keyboard::Key::Space);
    controls.addJumpKey(sf::Keyboard::Key::Up);
    controls.addJumpKey(sf::Keyboard::Key::W);

    controls.addRightKey(sf::Keyboard::Key::Right);
    controls.addRightKey(sf::Keyboard::Key::D);

    controls.addLeftKey(sf::Keyboard::Key::Left);
    controls.addLeftKey(sf::Keyboard::Key::A);

    controls.setShootButton(sf::Mouse::Button::Left);

    return controls;
}

int main() {

    const b2Vec2 gravity(0.0f, 2.f);
    const sf::Vector2u screen_size {1600, 1000};

    auto* window = new sf::RenderWindow();
    window->create(sf::VideoMode(screen_size.x, screen_size.y), "My window");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    auto* level = new Level(gravity, window);



    Player* player = level->createPlayer({0, 0}, {1, 2}, Animator(), getDefaultControls());
    player->animator->createAnimation("running", {(*level->textures)["pistol_bullet_frame1_texture"], (*level->textures)["pistol_bullet_frame2_texture"]}, 10);
    player->animator->createAnimation("idle", {(*level->textures)["pistol_bullet_frame1_texture"]}, 1);

    level->createStatic({-70, 25}, {200, 3}, (*level->textures)["pistol_texture"]);
    level->createStatic({30, 17}, {4, 4}, (*level->textures)["pistol_texture"]);
    level->createStatic({18, 18.5}, {1.2, 1}, (*level->textures)["pistol_texture"]);
    level->createStatic({24, 17.25}, {1.2, 1}, (*level->textures)["pistol_texture"]);
    level->createStatic({36, 20}, {1.2, 1}, (*level->textures)["pistol_texture"]);
    level->createStatic({42, 16.5}, {1.2, 1}, (*level->textures)["pistol_texture"]);
    level->createObject(b2_dynamicBody, {-10, 0}, {3, 3}, (*level->textures)["pistol_texture"]);

    level->player->setWeapon(level->getPistol());

    render(level);

    delete level;

    return 0;
}
