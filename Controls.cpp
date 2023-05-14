#include "Controls.h"


bool Controls::jumpPressed() const {
    return std::any_of(
            jumpKeys->cbegin(),
            jumpKeys->cend(),
            [](sf::Keyboard::Key key){return sf::Keyboard::isKeyPressed(key);});
}

bool Controls::rightPressed() const {
    return std::any_of(
            rightKeys->cbegin(),
            rightKeys->cend(),
            [](sf::Keyboard::Key key){return sf::Keyboard::isKeyPressed(key);});
}

bool Controls::leftPressed() const {
    return std::any_of(
            leftKeys->cbegin(),
            leftKeys->cend(),
            [](sf::Keyboard::Key key){return sf::Keyboard::isKeyPressed(key);});
}

bool Controls::shootPressed() const {
    return sf::Mouse::isButtonPressed(shootButton);
}

Controls::~Controls() {
    delete jumpKeys;
    delete rightKeys;
    delete leftKeys;
}

void Controls::addJumpKey(sf::Keyboard::Key key) const {
    jumpKeys->push_back(key);
}

void Controls::addRightKey(sf::Keyboard::Key key) const {
    rightKeys->push_back(key);
}

void Controls::addLeftKey(sf::Keyboard::Key key) const {
    leftKeys->push_back(key);
}

void Controls::setShootButton(sf::Mouse::Button button) {
    shootButton = button;
}

Controls::Controls() :
        jumpKeys(new std::vector<sf::Keyboard::Key>()),
        rightKeys(new std::vector<sf::Keyboard::Key>()),
        leftKeys(new std::vector<sf::Keyboard::Key>())
        { }
