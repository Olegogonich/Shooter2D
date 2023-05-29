#include "Game.h"

Game::Game() : levels(new std::vector<Level*>()), window(nullptr), currentLevelIndex(0) { }
void Game::start() {
    const sf::Vector2u screen_size {1600, 1000};

    window = new sf::RenderWindow();
    window->create(sf::VideoMode(screen_size.x, screen_size.y), "Shooter2D");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    loadLevel(first_level_path);

    sf::Text text;

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return;
            }
        }
        window->clear(sf::Color::White);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            currentLevelIndex++;

        currentLevelIndex %= 3;

        text.setString(std::to_string(10));
        text.setCharacterSize(10);
        sf::Color color = 1 ? sf::Color::Black : sf::Color::Red;
        text.setFillColor(color);
        text.setPosition({0, 0});
        window->draw(text);

        window->display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            startLevel(levels->at(currentLevelIndex));
    }
}

Level* Game::loadLevel(const std::string &path) {
    auto* level = new Level(gravity, window);
    auto* fin = new std::ifstream(path);
    std::string buffer;
    std::cout << "\nloading textures..." << '\n';
    loadLevelTextures(level, fin);
    std::cout << "\nloading fonts..." << '\n';
    loadLevelFonts(level, fin);
    std::cout << "\nloading players..." << '\n';
    getline(*fin, buffer);
    while (buffer == "player:") {
        createLevelPlayer(level, fin);
        getline(*fin, buffer);
    }
    std::cout << "\nloading enemies..." << '\n';
    getline(*fin, buffer);
    while (buffer == "enemy:") {
        createLevelEnemy(level, fin);
        getline(*fin, buffer);
    }
    std::cout << "\nloading dynamic..." << '\n';
    getline(*fin, buffer);
    while (buffer == "dynamic:") {
        createLevelDynamic(level, fin);
        getline(*fin, buffer);
    }
    std::cout << "\nloading static..." << '\n';
    getline(*fin, buffer);
    while (buffer == "static:") {
        createLevelStatic(level, fin);
        getline(*fin, buffer);
    }
    levels->push_back(level);
    delete fin;
    return level;
}

void Game::startLevel(Level *level) {

    level->start();
}

void Game::stop() {
    delete this;
}

void Game::loadLevelTextures(Level *level, std::ifstream* fin) {
    std::string buffer;
    std::getline(*fin, buffer);
    std::getline(*fin, buffer);
    for (; !buffer.empty(); std::getline(*fin, buffer)) {
        if (buffer.empty())
            continue;
        std::string name = buffer.substr(0, buffer.find(" = "));
        std::string path = buffer.substr(buffer.find(" = ") + 3);
        level->loadTexture(name, path);
    }
}

void Game::loadLevelFonts(Level *level, std::ifstream* fin) {
    std::string buffer;
    getline(*fin, buffer);
    getline(*fin, buffer);
    while (!buffer.empty()) {
        std::string name = buffer.substr(0, buffer.find(" = "));
        std::string path = buffer.substr(buffer.find(" = ") + 3);
        level->loadFont(name, path);
        std::getline(*fin, buffer);
    }
}

void Game::createLevelPlayer(Level *level, std::ifstream* fin) {
    std::string buffer, animations_path;
    sf::Vector2f pos, size;
    getline(*fin, buffer);
    pos.x = stof(buffer.substr(5, buffer.find(", ") - 5));
    pos.y = stof(buffer.substr(buffer.find(", ") + 2));
    getline(*fin, buffer);
    size.x = stof(buffer.substr(6, buffer.find(", ") - 6));
    size.y = stof(buffer.substr(buffer.find(", ") + 2));
    getline(*fin, buffer);
    animations_path = buffer.substr(12);

    Player* player = level->createPlayer(pos, size, Animator(), getDefaultControls());

    createEntityDefaultAnimations(level, player, animations_path);
}

void Game::createLevelEnemy(Level* level, std::ifstream* fin) {
    std::string buffer, animations_path;
    sf::Vector2f pos, size;
    for (; buffer.empty(); getline(*fin, buffer)) { }
    pos.x = stof(buffer.substr(5, buffer.find(", ") - 5));
    pos.y = stof(buffer.substr(buffer.find(", ") + 2));
    getline(*fin, buffer);
    size.x = stof(buffer.substr(6, buffer.find(", ") - 6));
    size.y = stof(buffer.substr(buffer.find(", ") + 2));
    getline(*fin, buffer);
    animations_path = buffer.substr(12);

    Enemy* enemy = level->createEnemy(pos, size, Animator());

    createEntityDefaultAnimations(level, enemy, animations_path);
}

void Game::createLevelStatic(Level *level, std::ifstream* fin) {
    createLevelObject(b2_staticBody, level, fin);
}

void Game::createLevelDynamic(Level *level, std::ifstream* fin) {
    createLevelObject(b2_dynamicBody, level, fin);
}

Controls Game::getDefaultControls() {
    Controls controls;

    controls.addJumpKey(sf::Keyboard::Key::Space);
    controls.addJumpKey(sf::Keyboard::Key::Up);
    controls.addJumpKey(sf::Keyboard::Key::W);

    controls.addRightKey(sf::Keyboard::Key::Right);
    controls.addRightKey(sf::Keyboard::Key::D);

    controls.addLeftKey(sf::Keyboard::Key::Left);
    controls.addLeftKey(sf::Keyboard::Key::A);

    controls.addReloadKey(sf::Keyboard::Key::R);

    controls.setShootButton(sf::Mouse::Button::Left);

    return controls;
}

void Game::createObjectDefaultAnimations(Level* level, PhysicalObject* object, const std::string& path) {
    std::ifstream fin (path);
    std::string buffer, name;
    getline(fin, buffer);
    while (getline(fin, name, ':')) {
        if (name.empty())
            continue;
        getline(fin, buffer);
        std::vector<sf::Texture *> textures = std::vector<sf::Texture *>();
        for (; buffer.find("frames_till_next") == std::string::npos; std::getline(fin, buffer)) {
            if (buffer.empty())
                continue;
            textures.push_back((*level->textures)[buffer]);
        }
        uint frames_till_next = std::stoul(buffer.substr(19));
        object->animator->createAnimation(name, textures, frames_till_next);
    }
    object->animator->setFixedSize(true);
}

void Game::createEntityDefaultAnimations(Level* level, Entity* entity, const std::string& path) {
    std::ifstream fin (path);
    std::string buffer, name;
    getline(fin, buffer);
    while (getline(fin, name, ':')) {
        if (name.empty())
            continue;
        getline(fin, buffer);
        std::vector<sf::Texture *> textures = std::vector<sf::Texture *>();
        for (; buffer.find("frames_till_next") == std::string::npos; std::getline(fin, buffer)) {
            if (buffer.empty())
                continue;
            textures.push_back((*level->textures)[buffer]);
        }
        uint frames_till_next = std::stoul(buffer.substr(19));
        entity->animator->createAnimation(name, textures, frames_till_next);
    }
    entity->animator->setFixedSize(true);
    // change
    entity->setWeapon(level->getPistol());
}

void Game::createLevelObject(const b2BodyType& type, Level *level, std::ifstream *fin) {
    std::string buffer, animations_path;
    sf::Vector2f pos, size;
    for (; buffer.empty(); getline(*fin, buffer)) { }
    pos.x = stof(buffer.substr(5, buffer.find(", ") - 5));
    pos.y = stof(buffer.substr(buffer.find(", ") + 2));
    getline(*fin, buffer);
    size.x = stof(buffer.substr(6, buffer.find(", ") - 6));
    size.y = stof(buffer.substr(buffer.find(", ") + 2));
    getline(*fin, buffer);

    if (buffer.substr(0, 11) == "animations:") {
        PhysicalObject* object = level->createObject(type, pos, size, Animator());
        animations_path = buffer.substr(12);
        createObjectDefaultAnimations(level, object, animations_path);
    }
    else if (buffer.substr(0, 8) == "texture:") {
        std::string texture_name = buffer.substr(9);
        level->createObject(type, pos, size, Animator::newStaticTexture((*level->textures)[texture_name]));
    }
}

Game::~Game() {
    for (Level* level : *levels) {
        delete level;
    }
    delete window;
}
