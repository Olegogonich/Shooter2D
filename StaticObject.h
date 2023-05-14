#pragma once
#include "GameObject.h"

struct StaticObject : GameObject {

    Animator* animator = new Animator();

    StaticObject(b2World*, const sf::Vector2f&, const sf::Vector2f&, sf::Texture*);
};
