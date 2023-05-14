#include "Player.h"
#include <iostream>

Player::Player(
        b2World *world,
        const sf::Vector2f &pos,
        const sf::Vector2f &size,
        Animator *_animator,
        Controls *_controls
        )
        : GameObject(world, b2_dynamicBody, pos, size, _animator) {

    body->SetFixedRotation(true);
    controls = _controls;
}

void Player::update() {
    updateShapePosition();
    updateShapeRotation();
    animator->update({body->GetPosition().x, body->GetPosition().y}, body->GetAngle());
    control();
}

void Player::stop() {
    if (body->GetContactList() == nullptr)
        return;

    b2Vec2 vel = body->GetLinearVelocity();
    body->SetLinearVelocity({vel.x * friction, vel.y});
}

bool Player::isOnFloor() const {
    return abs(body->GetLinearVelocity().y) < 0.00001f;
}

void Player::shoot() {

}

void Player::jump()  {
    if (controls->jumpPressed() && isOnFloor()) {
        float impulse = body->GetMass() * -jump_force;
        body->ApplyLinearImpulse({0.f, impulse}, body->GetWorldCenter(), true);
        // animator->currentAnimation = "jumping";
    }
}

void Player::move() {
    bool right = controls->rightPressed();
    bool left = controls->leftPressed();

    if (!right && !left) {
        stop();
        return;
    }

    if (right) {
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = vel.x <= top_speed ? vel.x + acceleration : top_speed;
        body->SetLinearVelocity(vel);
    }

    if (left) {
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = vel.x >= -top_speed ? vel.x - acceleration : -top_speed;
        body->SetLinearVelocity(vel);
    }

    animator->currentAnimation = "running";
}

void Player::control() {
    animator->currentAnimation = "idle";
    jump();
    move();
}