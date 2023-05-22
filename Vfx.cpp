#include "Vfx.h"

Vfx::Vfx(const Animation &animation, const sf::Vector2f &pos, const sf::Vector2f &size, const float &angle, const bool &cycle, const bool &stopAtLast) :
    animation(new Animation(animation)), pos(pos), size(size.x * zoom / antizoom * 2, size.y * zoom / antizoom * 2), angle(angle), cycle(cycle), stopAtLast(stopAtLast), sprite(new sf::Sprite()), played(false) { }

Vfx::Vfx(const Vfx &t) : Vfx(*t.animation, t.pos, t.size, t.angle, t.cycle, t.stopAtLast) {
    sprite = new sf::Sprite(*t.sprite);
}

void Vfx::update() {
    updateSprite();
    sprite->setTexture(*animation->getCurrentTexture());

    if (animation->frame != animation->textures->size() * animation->framesTillNext - 1 || cycle)
        animation->update();
    else if (!stopAtLast)
        played = true;
}

void Vfx::updateSprite() const {
    sf::Vector2u textureSize = animation->getCurrentTexture()->getSize();
    sf::Vector2f scaling = {size.x / (float)textureSize.x, size.y / (float)textureSize.y};
    sprite->setScale(scaling);
    sprite->setOrigin((float)textureSize.x * 0.5f, (float)textureSize.y * 0.5f);
    sprite->setPosition({pos.x * zoom, pos.y * zoom});
    sprite->setRotation(angle * RADTODEG);
}

Vfx::~Vfx() {
    delete sprite;
    delete animation;
}
