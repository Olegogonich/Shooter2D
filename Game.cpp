#include "Game.h"

Game::Game(sf::RenderWindow* window) : levels(new std::vector<Level*>()), window(window) { }

void Game::start() {
    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop();
                return;
            }
        }
        window->clear(sf::Color::White);



        window->display();
    }
}

Level* Game::loadLevel(const std::string &path) {
    auto* level = new Level(gravity, window);

}

void Game::startLevel(Level *level) {
    level->start();

}

void Game::stop() {
    delete this;
}

Game::~Game() {
    for (Level* level : *levels) {
        delete level;
    }
}

void Game::loadLevelTextures(Level *level, std::ifstream* fin) {
    std::string buffer;
    std::getline(*fin, buffer);

    for (; buffer != "player:"; std::getline(*fin, buffer)) {
        std::string name = buffer.substr(0, buffer.find(" = "));
        std::string path = buffer.substr(buffer.find(" = ") + 1);
        std::cout << name << " = " << path << '\n';
        level->loadTexture(name, path);
    }
}

void Game::loadLevelFonts(Level *level, std::ifstream* fin) {

}

void Game::createLevelPlayers(Level *level, std::ifstream* fin) {

}

void Game::createLevelEnemies(Level *level, std::ifstream* fin) {

}

void Game::createLevelStaics(Level *level, std::ifstream* fin) {

}

void Game::createLevelDynamics(Level *level, std::ifstream* fin) {

}
