#include "Animator.h"

Animator::Animator() {
    animations = new std::map<std::string, Animation*>();
    sprite = new sf::Sprite();
}

void Animator::update(const sf::Vector2f& pos, const float& rotation) const {
    getCurrentAnimation()->update();
    updateSprite(pos, rotation);
}

void Animator::updateSprite(const sf::Vector2f& pos, const float& rotation) const {
    sprite->setTexture(*getCurrentTexture());
    sprite->setPosition({pos.x * zoom, pos.y * zoom});
    sprite->setRotation(rotation * RADTODEG);
}

sf::Texture* Animator::getCurrentTexture() const {
    return getCurrentAnimation()->getCurrentTexture();
}

Animation* Animator::getCurrentAnimation() const {
    return animations->at(currentAnimationName);
}

void Animator::createAnimation(const std::string& name, std::vector<sf::Texture*>* textures, uint framesTillNext) const {
    (*animations)[name] = new Animation(textures, framesTillNext);
}

Animator::~Animator() {
    for (const auto& animation : *animations) {
        delete animation.second;
    }
    delete animations;
    delete sprite;
}