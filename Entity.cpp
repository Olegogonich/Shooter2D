#include "Entity.h"

Entity::Entity(b2World& world, const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& _animator, const int& _health, const float& _jump_force, const float& _top_speed, const float& _acceleration, const float& _friction)
: PhysicalObject(world, b2_dynamicBody, pos, size, _animator) {
    health = _health;
    jump_force = _jump_force;
    top_speed = _top_speed;
    acceleration = _acceleration;
    friction = _friction;
    cannotShoot = 0;
    shooting = false;
    reloading = false;
    body->SetFixedRotation(true);
    weapon = nullptr;
}

void Entity::setWeapon(const Weapon& _weapon) {
    delete weapon;
    weapon = new Weapon(_weapon);
}

void Entity::update() {
    PhysicalObject::update();

    animator->update({body->GetPosition().x, body->GetPosition().y}, {size.x * zoom * 2.f, size.y * zoom * 2.f}, body->GetAngle());

    if (weapon == nullptr)
        return;

    weapon->angle = aimingAngle;

    if (weapon->angle > -90 * DEGTORAD && weapon->angle < 90 * DEGTORAD) {
        weapon->angle -= weapon->current_recoil * DEGTORAD;
        weapon->weaponAnimator->currentAnimation = "idle";
    } else {
        weapon->angle += weapon->current_recoil * DEGTORAD;
        weapon->weaponAnimator->currentAnimation = "idle_bottom";
    }
    if (shooting)
        weapon->weaponAnimator->currentAnimation = (weapon->angle > -90 * DEGTORAD && weapon->angle < 90 * DEGTORAD) ? "firing" : "firing_bottom";

    weapon->weaponAnimator->update({body->GetPosition().x, body->GetPosition().y}, {1.f * zoom, 0.45f * zoom}, weapon->angle);

    updateShooting();
}

void Entity::updateShooting() {
    if (reloading && cannotShoot == 0) {
        weapon->ammo = weapon->capacity;
        reloading = false;
    }
    shooting = false;

    weapon->current_recoil *= 1 - weapon->stability;
    cannotShoot -= cannotShoot > 0 ? 1 : 0;
}

bool Entity::isOnFloor() const {
    return body->GetLinearVelocity().y == 0.f;
}

void Entity::shoot() {
    if (weapon == nullptr || weapon->ammo <= 0 || cannotShoot != 0)
        return;

    weapon->current_recoil += weapon->recoil;

    if(weapon->current_recoil > weapon->max_recoil)
        weapon->current_recoil = weapon->max_recoil;

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
    body->ApplyLinearImpulseToCenter({0, impulse}, true);
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

void Entity::dealDamage(const uint& damage) {
    health -= damage;
}

bool Entity::isDead() const {
    return health <= 0;
}

Entity::~Entity() {
    delete weapon;
}
