#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

struct Controls {

    std::vector<sf::Keyboard::Key>* jumpKeys;
    std::vector<sf::Keyboard::Key>* rightKeys;
    std::vector<sf::Keyboard::Key>* leftKeys;
    sf::Mouse::Button shootButton;

    Controls();

    void addJumpKey(sf::Keyboard::Key) const;

    void addRightKey(sf::Keyboard::Key) const;

    void addLeftKey(sf::Keyboard::Key) const;

    void setShootButton(sf::Mouse::Button);

    bool jumpPressed() const;

    bool rightPressed() const;

    bool leftPressed() const;

    bool shootPressed() const;

    ~Controls();
};

