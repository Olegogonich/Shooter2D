#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(b2World& world, const b2BodyType& type, sf::Vector2f pos, sf::Vector2f _size, const Animator& _animator) {
    shape = new sf::RectangleShape();
    animator = new Animator(_animator);
    size = _size;

    b2BodyDef bodyDef;
    bodyDef.type = type;
    pos.x /= antizoom;
    pos.y /= antizoom;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angle = 0;

    b2PolygonShape boxShape;
    size.x /= antizoom;
    size.y /= antizoom;
    boxShape.SetAsBox(size.x, size.y);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 0.1;
//    boxFixtureDef.friction = 0;

    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&boxFixtureDef);

    shape->setFillColor(sf::Color::Black);
    shape->setSize({size.x * 2.f * zoom, size.y * 2.f * zoom});
    shape->setOrigin(shape->getSize().x * 0.5f, shape->getSize().y * 0.5f);
    shape->setPosition(shape->getPosition().x * zoom, shape->getPosition().y * zoom);

}

PhysicalObject::PhysicalObject(b2World &world, const b2BodyType& type, sf::Vector2f pos, const sf::Vector2f size, sf::Texture* _texture) :
    PhysicalObject(world, type, pos, size, Animator::newStaticTexture(_texture)) { }

void PhysicalObject::update() {
    updateShapePosition();
    updateShapeRotation();
    animator->update({body->GetPosition().x, body->GetPosition().y}, shape->getSize(), body->GetAngle());
}

void PhysicalObject::updateShapePosition() const {
    auto pos = body->GetPosition();
    shape->setPosition(pos.x * zoom, pos.y * zoom);
}

void PhysicalObject::updateShapeRotation() const {
    shape->setRotation(body->GetAngle() * RADTODEG);
}

PhysicalObject::~PhysicalObject() {
    body->GetWorld()->DestroyBody(body);
    delete shape;
    delete animator;
}

