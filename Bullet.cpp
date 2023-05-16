#include "Bullet.h"

Bullet::Bullet(b2World& world, const sf::Vector2f &pos, const sf::Vector2f &size, const float& _angle, const float& _power, sf::Texture* _texture)
    : PhysicalObject(world, b2_dynamicBody, pos, size, Animator::newStaticTexture(_texture)) {
    body->SetBullet(true);
    body->SetLinearDamping(0.f);
    angle = _angle;
    power = _power;
    body->SetTransform({pos.x / antizoom, pos.y / antizoom}, angle);
    body->SetLinearVelocity({cos(angle) * power, sin(angle) * power});
}

Bullet::Bullet(b2World& world, const sf::Vector2f &pos, const sf::Vector2f &size, const float& _angle, const float& _power, const Animator& _animator)
    : PhysicalObject(world, b2_dynamicBody, pos, size, _animator) {
    body->SetBullet(true);
    body->SetLinearDamping(0.f);
    angle = _angle;
    power = _power;
    body->SetTransform({pos.x / antizoom + cos(angle) * 1.f, pos.y / antizoom + sin(angle) * 1.f}, angle);
    body->SetLinearVelocity({cos(angle) * power, sin(angle) * power});
}

void Bullet::update() {
    updateShapePosition();
    updateShapeRotation();
    animator->update({body->GetPosition().x, body->GetPosition().y}, body->GetAngle());
}

