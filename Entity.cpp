#include "Entity.h"

Entity::Entity(b2World& world, const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& _animator, const float& _jump_force, const float& _top_speed, const float& _acceleration, const float& _friction)
: PhysicalObject(world, b2_dynamicBody, pos, size, _animator) {
    jump_force = _jump_force;
    top_speed = _top_speed;
    acceleration = _acceleration;
    friction = _friction;
    cannotShoot = 0;
    shooting = false;
    reloading = false;
    body->SetFixedRotation(true);
}

void Entity::setWeapon(const Weapon& _weapon) {
    weapon = new Weapon(_weapon);
}

void Entity::update() {
    PhysicalObject::update();
    animator->update({body->GetPosition().x, body->GetPosition().y}, shape->getSize(), body->GetAngle());

    if (reloading && cannotShoot == 0) {
        weapon->ammo = weapon->capacity;
        reloading = false;
    }
    shooting = false;

    cannotShoot -= cannotShoot > 0 ? 1 : 0;
}

bool Entity::isOnFloor() const {
    return body->GetLinearVelocity().y == 0.f;
}

void Entity::shoot() {

    if (weapon == nullptr || weapon->ammo <= 0 || cannotShoot != 0)
        return;

    weapon->ammo--;
    cannotShoot = weapon->rate;
    shooting = true;
}

void Entity::reload() {
    if (weapon == nullptr || reloading || weapon->ammo == weapon->capacity)
        return;

    cannotShoot = weapon->reload_time;
    reloading = true;
}

void Entity::stop() {
    if (body->GetContactList() == nullptr)
        return;

    b2Vec2 vel = body->GetLinearVelocity();
    body->SetLinearVelocity({vel.x * friction, vel.y});
}

void Entity::jump()  {
    float impulse = body->GetMass() * -jump_force;
    body->ApplyLinearImpulse({0.f, impulse}, body->GetWorldCenter(), true);
}

void Entity::moveRight() {
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = vel.x <= top_speed ? vel.x + acceleration : top_speed;
    body->SetLinearVelocity(vel);
}

void Entity::moveLeft() {
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = vel.x >= -top_speed ? vel.x - acceleration : -top_speed;
    body->SetLinearVelocity(vel);
}

Entity::~Entity() {
    delete weapon;
}
