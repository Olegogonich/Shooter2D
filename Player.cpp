#include "Player.h"


Player::Player(b2World *world, const b2BodyType &type, const sf::Vector2f& pos, const sf::Vector2f& size) :
    GameObject(world, type, pos, size) { }

void Player::update() const {
    updateShapePosition();
    updateShapeRotation();
    control();
}

void Player::jump(float height) const {
    if (body->GetLinearVelocity().y != 0.f)
        return;

    body->ApplyLinearImpulseToCenter({0.f, height * 5000.f}, true);
}

void Player::walk(float speed) const {
    b2Vec2 vel = body->GetLinearVelocity();
    body->SetLinearVelocity({speed * 100, vel.y});
}

void Player::stop(float friction) const {
    if (body->GetContactList() == nullptr)
        return;

    b2Vec2 vel = body->GetLinearVelocity();
    body->SetLinearVelocity({vel.x * friction, vel.y * friction});
}

void Player::control() const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        jump(-jump_force);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        jump(-jump_force);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        jump(-jump_force);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        walk(-walking_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        walk(walking_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        walk(-walking_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        walk(walking_speed);
    }
}