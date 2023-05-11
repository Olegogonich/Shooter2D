#include "GameObject.h"

#define zoom 10
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

GameObject::GameObject(b2World *world, const b2BodyType& type, sf::Vector2f pos, sf::Vector2f size, Animator* _animator) {
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angle = 0;

    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x, size.y);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 0;

    body = world->CreateBody(&bodyDef);
    body->CreateFixture(&boxFixtureDef);

    animator = _animator;
    animator->sprite->setTexture(*animator->getCurrentTexture());
    animator->sprite->setScale(0.2f, 0.2f);
    animator->sprite->setPosition(pos.x * zoom, pos.y * zoom);

    shape = new sf::RectangleShape();
    shape->setFillColor(sf::Color::Black);
    shape->setSize({size.x * 2.f * zoom, size.y * 2.f * zoom});
    shape->setOrigin(shape->getSize().x * 0.5f, shape->getSize().y * 0.5f);
    shape->setPosition(shape->getPosition().x * zoom, shape->getPosition().y * zoom);
}

void GameObject::update() const {
    updateShapePosition();
    updateShapeRotation();
    animator->update({body->GetPosition().x, body->GetPosition().y}, body->GetAngle());
}

void GameObject::updateShapePosition() const {
    auto pos = body->GetPosition();
    shape->setPosition(pos.x * zoom, pos.y * zoom);
}

void GameObject::updateShapeRotation() const {
    shape->setRotation(body->GetAngle() * RADTODEG);
}

std::string GameObject::toStringShapePosition() const {
    return std::to_string(shape->getPosition().x) + " " + std::to_string(shape->getPosition().y);
}

std::string GameObject::toStringBodyPosition() const {
    return std::to_string(body->GetPosition().x) + " " + std::to_string(body->GetPosition().y) + " " + std::to_string(body->GetAngle());
}

GameObject::~GameObject() {
    delete shape;
    delete animator;
}
