#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <fstream>
#include "Level.h"

#define CONTENT_ROOT "/Users/oleh/CLionProjects/Shooter2D/"

class Game {

public:
    void start();

    void stop();

    Game();

    ~Game();

private:
    sf::RenderWindow* window;
    std::vector<std::string> levels;

    int currentLevelIndex;

    static void startLevel(Level*);

    Level* loadLevel(const std::string& path);

    static void loadLevelTextures(Level*, std::ifstream*);

    static void loadLevelFonts(Level*, std::ifstream*);

    static void createEntityDefaultAnimations(Level*, Entity*, const std::string& path);

    static void createLevelPlayer(Level *level, std::ifstream *fin);

    static void createLevelEnemy(Level*, std::ifstream*);

    static void createLevelStatic(Level *level, std::ifstream *fin);

    static void createLevelDynamic(Level*, std::ifstream*);

    static void createLevelObject(const b2BodyType&, Level*, std::ifstream*);

    static void setLevelWinningPos(Level*, const std::string&);

    static Controls getDefaultControls();

    static void createObjectDefaultAnimations(Level *, PhysicalObject *, const std::string &);
};
