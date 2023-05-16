#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"

struct Animation {
    std::vector<sf::Texture*>* textures;
    uint frame;
    uint framesTillNext;

    Animation(const std::vector<sf::Texture*>&, uint);

    Animation(const Animation&);

    void update();

    void reset();

    sf::Texture* getCurrentTexture() const;

    ~Animation();
};
