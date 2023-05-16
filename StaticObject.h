#pragma once
#include "PhysicalObject.h"

struct StaticObject : PhysicalObject {

    StaticObject(b2World& world, const sf::Vector2f& pos, const sf::Vector2f& size, sf::Texture* texture);
};
