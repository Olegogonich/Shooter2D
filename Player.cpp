#include "Player.h"
#include <iostream>

Player::Player(b2World *world, const b2BodyType &type, const sf::Vector2f& pos, const sf::Vector2f& size, Animator* _animator) :
    GameObject(world, type, pos, size, _animator) { }

void Player::update() const {
    updateShapePosition();
    updateShapeRotation();
    control();
}

void Player::jump(float height) const {
    if (body->GetLinearVelocity().y != 0.f)
        return;
    b2Vec2 vel = body->GetLinearVelocity();
    body->ApplyLinearImpulseToCenter({vel.x, height * 5000.f}, true);
}

void Player::walk(float speed) const {
    b2Vec2 vel = body->GetLinearVelocity();
    body->ApplyLinearImpulseToCenter({speed * 100, vel.y}, true);
}

void Player::stop(float friction) const {
    if (body->GetContactList() == nullptr)
        return;

    b2Vec2 vel = body->GetLinearVelocity();
    body->SetLinearVelocity({vel.x * friction, vel.y});
}

void Player::control() const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
     || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
     || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        jump(-jump_force);
    }
    if (body->GetContactList() == nullptr)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
     || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        walk(-walking_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
     || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        walk(walking_speed);
    }
//        stop(friction);
}