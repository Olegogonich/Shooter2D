#include "Bullet.h"

Bullet::Bullet(b2World& world, const sf::Vector2f &pos, const sf::Vector2f &size, const uint& _damage, const float& _angle, const float& _power, const float& bulletMass, const Animator& _animator)
    : PhysicalObject(world, bullet_body_type, pos, size, _animator) {
    damage = _damage;
    angle = _angle;
    power = _power;
    b2MassData massData = body->GetMassData();
    massData.mass = bulletMass;
    lifetime = bullet_lifetime;
    body->SetBullet(true);
    body->SetLinearDamping(0.f);
    body->SetMassData(&massData);
    body->SetTransform({pos.x / antizoom, pos.y / antizoom}, angle);
    body->SetLinearVelocity({cos(angle) * power, sin(angle) * power});
    owner = nullptr;
}

void Bullet::update() {
    PhysicalObject::update();
    animator->update({body->GetPosition().x, body->GetPosition().y}, shape->getSize(), body->GetAngle());
    lifetime--;
}

void Bullet::setOwner(Entity* _owner) {
    owner = _owner;
}

void Bullet::resetOwner() {
    owner = nullptr;
}

Bullet::~Bullet() = default;
