#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Animation.h"

struct Animator {

    std::map<std::string, Animation*>* animations;
    sf::Sprite* sprite;
    std::string currentAnimation;

    struct AnimatorException : public std::exception {

        const std::string m_msg;

        explicit AnimatorException(std::string msg);

        const char* what() const noexcept override;
    };

    Animator();

    Animator *setStaticTexture(sf::Texture*);

    void updateSprite(const sf::Vector2f&, const float&) const;

    void update(const sf::Vector2f&, const float&) const;

    sf::Texture* getCurrentTexture() const;

    Animation* getCurrentAnimation() const;

    void createAnimation(const std::string&, std::vector<sf::Texture*>*, uint) const;

    ~Animator();
};
