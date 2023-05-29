#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <utility>
#include <vector>

#include "Animation.h"

struct Animator {

    std::map<std::string, Animation*>* animations;
    sf::Sprite* sprite;
    std::string currentAnimation;
    bool fixedSize;

    Animator();

    Animator(const Animator&);

    void setStaticTexture(sf::Texture*);

    static Animator newStaticTexture(sf::Texture*);

    void updateSprite(const sf::Vector2f&, const sf::Vector2f&, const float&) const;

    void update(const sf::Vector2f&, const sf::Vector2f&, const float&) const;

    sf::Texture* getCurrentTexture() const;

    Animation* getCurrentAnimation() const;

    void setFixedSize(bool);

    void createAnimation(const std::string &name, const std::vector<sf::Texture*>& textures, uint framesTillNext);

    ~Animator();

    struct AnimatorException : public std::exception {

        const std::string m_msg;

        explicit AnimatorException(std::string msg);

        const char* what() const noexcept override;
    };
};
