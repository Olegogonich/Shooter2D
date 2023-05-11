#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Animation.h"

#define zoom 10
#define RADTODEG 57.295779513082320876f

struct Animator {

    std::map<std::string, Animation*>* animations;
    sf::Sprite* sprite;
    std::string currentAnimationName;

    Animator();

    void updateSprite(const sf::Vector2f&, const float&) const;

    void update(const sf::Vector2f&, const float&) const;

    sf::Texture* getCurrentTexture() const;

    Animation* getCurrentAnimation() const;

    void createAnimation(const std::string&, std::vector<sf::Texture*>*, uint) const;

    ~Animator();
};
