#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

struct Controls {

    std::vector<sf::Keyboard::Key>* jumpKeys;
    std::vector<sf::Keyboard::Key>* rightKeys;
    std::vector<sf::Keyboard::Key>* leftKeys;
    std::vector<sf::Keyboard::Key>* reloadKeys;
    sf::Mouse::Button shootButton;

    Controls();

    Controls(const Controls&);

    void addJumpKey(sf::Keyboard::Key) const;

    void addRightKey(sf::Keyboard::Key) const;

    void addLeftKey(sf::Keyboard::Key) const;

    void addReloadKey(sf::Keyboard::Key) const;

    void setShootButton(sf::Mouse::Button);

    bool jumpPressed() const;

    bool rightPressed() const;

    bool leftPressed() const;

    bool reloadPressed() const;

    bool shootPressed() const;

    ~Controls();
};

