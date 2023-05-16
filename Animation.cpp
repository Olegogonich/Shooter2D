#include "Animation.h"

Animation::Animation(const std::vector<sf::Texture*>& _textures, uint framesTillNext) : frame(0), framesTillNext(framesTillNext) {

    textures = new std::vector<sf::Texture*>();

    for (sf::Texture* texture : _textures) {
        textures->push_back(texture);
    }
}

Animation::Animation(const Animation& temp) : frame(0), framesTillNext(temp.framesTillNext), textures(temp.textures) { }

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

    delete textures;
}
