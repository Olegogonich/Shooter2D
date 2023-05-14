#include "StaticObject.h"

StaticObject::StaticObject(b2World *world, const sf::Vector2f &pos, const sf::Vector2f &size, sf::Texture *texture)
: GameObject(world, b2_staticBody, pos, size, (new Animator())->setStaticTexture(texture)) { }
