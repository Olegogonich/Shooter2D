#include <vector>
#include <iostream>
#include "Animation.h"

struct Vfx {
    sf::Vector2f pos;
    sf::Vector2f size;
    float angle;
    Animation* animation;
    sf::Sprite* sprite;
    bool cycle;
    bool stopAtLast;
    bool played;

    void update();

    void updateSprite() const;

    Vfx(const Animation&, const sf::Vector2f&, const sf::Vector2f&, const float&, const bool&, const bool&);

    Vfx(const Vfx&);

    ~Vfx();
};

