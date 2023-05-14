#include "Animator.h"

#include <utility>

Animator::Animator() {
    animations = new std::map<std::string, Animation*>();
    sprite = new sf::Sprite();
}

Animator* Animator::setStaticTexture(sf::Texture *texture) {
    currentAnimation.clear();
    sprite->setTexture(*texture);
    return this;
}

void Animator::update(const sf::Vector2f& pos, const float& rotation) const {
    if (currentAnimation.empty())
        return;

    getCurrentAnimation()->update();
    updateSprite(pos, rotation);
}

void Animator::updateSprite(const sf::Vector2f& pos, const float& rotation) const {
    sprite->setTexture(*getCurrentTexture());
    auto textureSize = getCurrentTexture()->getSize();
    sprite->setOrigin((float)textureSize.x * 0.5f, (float)textureSize.y * 0.5f);
    sprite->setPosition({pos.x * zoom, pos.y * zoom});
    sprite->setRotation(rotation * RADTODEG);
}

sf::Texture* Animator::getCurrentTexture() const {
    if (currentAnimation.empty()) {
        return const_cast<sf::Texture*>(sprite->getTexture());
    }
    return getCurrentAnimation()->getCurrentTexture();
}

Animation* Animator::getCurrentAnimation() const {
    if (!animations->count(currentAnimation)) {
        std::string exceptionText = "AnimatorException: no animation named \"" + currentAnimation + "\"";
        throw (AnimatorException(exceptionText));
    }

    return animations->at(currentAnimation);
}

void Animator::createAnimation(const std::string& name, std::vector<sf::Texture*>* textures, uint framesTillNext) const {
    (*animations)[name] = new Animation(textures, framesTillNext);
}

Animator::AnimatorException::AnimatorException(std::string msg) : m_msg(std::move(msg)) { }

const char *Animator::AnimatorException::what() const noexcept {
    return m_msg.c_str();
}

Animator::~Animator() {
    for (const auto& animation : *animations) {
        delete animation.second;
    }
    delete animations;
    delete sprite;
}
