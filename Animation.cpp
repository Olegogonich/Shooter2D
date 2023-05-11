#include "Animation.h"

Animation::Animation(std::vector<sf::Texture*>* _textures, uint framesTillNext) :
    textures(_textures), frame(0), framesTillNext(framesTillNext) { }

void Animation::update() {
    frame++;
    frame = frame % (textures->size() * framesTillNext);
}

void Animation::reset() {
    frame = 0;
}

sf::Texture* Animation::getCurrentTexture() const {
    return textures->at(frame / framesTillNext);
}

Animation::~Animation() {
    for (auto* texture : *textures) {
        delete texture;
    }
    delete textures;
}