#include "Controls.h"
#include <iostream>

bool Controls::jumpPressed() const {
    return std::any_of(jumpKeys->cbegin(),jumpKeys->cend(),[](sf::Keyboard::Key key){return sf::Keyboard::isKeyPressed(key);});
}

bool Controls::rightPressed() const {
    return std::any_of(rightKeys->cbegin(),rightKeys->cend(),[](sf::Keyboard::Key key){return sf::Keyboard::isKeyPressed(key);});
}

bool Controls::leftPressed() const {
    return std::any_of(leftKeys->cbegin(),leftKeys->cend(),[](sf::Keyboard::Key key){return sf::Keyboard::isKeyPressed(key);});
}

bool Controls::reloadPressed() const {
    return std::any_of(reloadKeys->cbegin(),reloadKeys->cend(),[](sf::Keyboard::Key key){return sf::Keyboard::isKeyPressed(key);});
}

bool Controls::shootPressed() const {
    return sf::Mouse::isButtonPressed(shootButton);
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

void Controls::addReloadKey(sf::Keyboard::Key key) const {
    reloadKeys->push_back(key);
}

void Controls::setShootButton(sf::Mouse::Button button) {
    shootButton = button;
}

Controls::Controls(const Controls& temp) :
        jumpKeys(new std::vector<sf::Keyboard::Key>(*temp.jumpKeys)),
        rightKeys(new std::vector<sf::Keyboard::Key>(*temp.rightKeys)),
        leftKeys(new std::vector<sf::Keyboard::Key>(*temp.leftKeys)),
        reloadKeys(new std::vector<sf::Keyboard::Key>(*temp.reloadKeys))
        { }

Controls::Controls() :
        jumpKeys(new std::vector<sf::Keyboard::Key>()),
        rightKeys(new std::vector<sf::Keyboard::Key>()),
        leftKeys(new std::vector<sf::Keyboard::Key>()),
        reloadKeys(new std::vector<sf::Keyboard::Key>())
        { }

Controls::~Controls() {
    delete jumpKeys;
    delete rightKeys;
    delete leftKeys;
}
