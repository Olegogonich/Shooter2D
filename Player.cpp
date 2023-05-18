#include "Player.h"

Player::Player(
        b2World& world,
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const Animator& _animator,
        const Controls& _controls
    ) :
    PhysicalObject(world, b2_dynamicBody, pos, size, _animator) {

    controls = new Controls(_controls);

    cannotShoot = 0;
    body->SetFixedRotation(true);
}

void Player::update() {
    updateShapePosition();
    updateShapeRotation();
    animator->update({body->GetPosition().x, body->GetPosition().y}, shape->getSize(), body->GetAngle());
    control();
}

void Player::stop() {
    if (body->GetContactList() == nullptr)
        return;

    b2Vec2 vel = body->GetLinearVelocity();
    body->SetLinearVelocity({vel.x * friction, vel.y});
}

bool Player::isOnFloor() const {
    return abs(body->GetLinearVelocity().y) < 0.0000001f;
}

bool Player::shoot() {
    cannotShoot -= cannotShoot > 0 ? 1 : 0;
    if (weapon == nullptr || !controls->shootPressed() || cannotShoot != 0)
        return false;

    cannotShoot = weapon->rate;

    return true;
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

void Player::setWeapon(const Weapon& _weapon) {
    weapon = new Weapon(_weapon);
}

Player::~Player() {
    delete controls;
    delete weapon;
}
