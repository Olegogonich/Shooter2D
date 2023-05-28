#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <fstream>
#include "Level.h"

class Game {

public:
    void start();

    void stop();

private:
    sf::RenderWindow* window;
    std::vector<Level*>* levels;

    uint currentLevelIndex;

    explicit Game(sf::RenderWindow*);

    void startLevel(Level*);

    Level* loadLevel(const std::string& path);

    void loadLevelTextures(Level*, std::ifstream*);

    void loadLevelFonts(Level*, std::ifstream*);

    void createLevelPlayers(Level*, std::ifstream*);

    void createLevelEnemies(Level*, std::ifstream*);

    void createLevelStaics(Level*, std::ifstream*);

    void createLevelDynamics(Level*, std::ifstream*);

    ~Game();
};
