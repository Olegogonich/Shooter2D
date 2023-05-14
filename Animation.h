#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"

struct Animation {
    std::vector<sf::Texture*>* textures;
    uint frame;
    uint framesTillNext;

    Animation(std::vector<sf::Texture*>* _textures, uint _framesTillNext);

    void update();

    void reset();

    sf::Texture* getCurrentTexture() const;

    ~Animation();
};
