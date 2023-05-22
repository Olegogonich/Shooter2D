#include "Vfx.h"

Vfx::Vfx(const Animator &animator, const sf::Vector2f &size, const float &angle, const bool &cycle, const bool &stopAtLast) :
    animator(new Animator(animator)), size(size), angle(angle), cycle(cycle), stopAtLast(stopAtLast) { }

Vfx::Vfx(const Vfx &temp) : animator(new Animator(*temp.animator)), cycle(temp.cycle), stopAtLast(temp.stopAtLast) { }

Vfx::~Vfx() {
    delete animator;
}

void Vfx::update() const {
//    animator->update({body->GetPosition().x, body->GetPosition().y}, {size.x * zoom * 2.f, size.y * zoom * 2.f}, body->GetAngle());
}