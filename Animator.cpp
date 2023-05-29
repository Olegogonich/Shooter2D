#include "Animator.h"

Animator::Animator() :
    animations(new std::map<std::string, Animation*>()),
    sprite(new sf::Sprite()),
    fixedSize(true) { }

Animator::Animator(const Animator& temp) :
    animations(new std::map<std::string, Animation*>()),
    sprite(new sf::Sprite(*temp.sprite)),
    currentAnimation(temp.currentAnimation),
    fixedSize(true) {

    for (const auto& animation : *temp.animations) {
        (*animations)[animation.first] = new Animation(*animation.second);
    }
}

Animator Animator::newStaticTexture(sf::Texture* texture) {
    Animator animator;
    animator.setStaticTexture(texture);
    return animator;
}

void Animator::setStaticTexture(sf::Texture* texture) {
    currentAnimation.clear();
    sprite->setTexture(*texture);
}

void Animator::update(const sf::Vector2f& pos, const sf::Vector2f& size, const float& rotation) const {
    updateSprite(pos, size, rotation);

    if (currentAnimation.empty())
        return;

    sprite->setTexture(*getCurrentTexture());
    getCurrentAnimation()->update();
}

void Animator::updateSprite(const sf::Vector2f& pos, const sf::Vector2f& size, const float& rotation) const {
    sf::Vector2u textureSize = getCurrentTexture()->getSize();
    if (fixedSize) {
        sf::Vector2f scaling = {size.x / (float) textureSize.x, size.y / (float) textureSize.y};
        sprite->setScale(scaling);
    }
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
        std::string exceptionText = "No animation named " + currentAnimation;
        throw (AnimatorException(exceptionText));
    }

    return animations->at(currentAnimation);
}

void Animator::createAnimation(const std::string& name, const std::vector<sf::Texture*>& textures, uint framesTillNext) {
    (*animations)[name] = new Animation(textures, framesTillNext);
    currentAnimation = name;
}

Animator::AnimatorException::AnimatorException(std::string msg) : m_msg(std::move(msg)) { }

const char *Animator::AnimatorException::what() const noexcept {
    return m_msg.c_str();
}

Animator::~Animator() {
    for (auto& animation : *animations) {
        delete animation.second;
    }
    delete animations;
    delete sprite;
}

void Animator::setFixedSize(bool flag) {
    fixedSize = flag;
}
