#include "Level.h"

Level::Level(const b2Vec2& gravity, sf::RenderWindow *window) :
    fonts(new std::map<std::string, sf::Font*>()),
    textures(new std::map<std::string, sf::Texture*>()),
    objects(new std::vector<PhysicalObject*>()),
    entities(new std::vector<Entity*>()),
    bullets(new std::vector<Bullet*>()),
    view(new sf::View(window->getDefaultView())),
    world(new b2World(gravity)),
    window(window) {
    loadDefaultTextures();
    loadDefaultFonts();
}

PhysicalObject* Level::createObject(const b2BodyType& type, const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& animator) const {
    auto* object = new PhysicalObject(*this->world, type, pos, size, animator);
    objects->push_back(object);
    return object;
}

PhysicalObject* Level::createStatic(const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& animator) const {
    return createObject(b2_staticBody, pos, size, animator);
}

PhysicalObject* Level::createDynamic(const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& animator) const {
    return createObject(b2_dynamicBody, pos, size, animator);
}

Player* Level::createPlayer(const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& animator, const Controls& controls) {
    auto* object = new Player(*this->world, pos, size, animator, controls);
    entities->push_back(object);
    player = object;
    return object;
}

Bullet* Level::createBullet(const sf::Vector2f& pos, const sf::Vector2f& size, const uint& damage, const float& angle, const float& power, const Animator& animator) const {
    auto* object = new Bullet(*this->world, pos, size, damage, angle, power, animator);
    objects->push_back(object);
    bullets->push_back(object);
    return object;
}

sf::Texture* Level::loadTexture(const std::string& name, const std::string& path) const {
     auto* texture = new sf::Texture();

    if (!texture->loadFromFile(path)) {
        std::cout << "file not found" << '\n';
        return nullptr;
    }
    texture->setSmooth(true);
    (*textures)[name] = texture;

    return texture;
}

void Level::checkShooting() const {

    for (Entity* entity : *entities) {
        if (!entity->shooting)
            return;

        b2Vec2 entityPos = entity->body->GetPosition();
        float angle = getMouseToEntityAngle(entity);

        Bullet *bullet = createBullet(
                {
                        entityPos.x * antizoom,
                        entityPos.y * antizoom
                },
                {
                        entity->weapon->bullet_size,
                        entity->weapon->bullet_size
                },
                entity->weapon->damage,
                angle,
                entity->weapon->power,
                entity->weapon->bulletAnimator
        );

        b2Vec2 bulletPos;
        while (Level::collide(bullet, entity)) {
            bulletPos = bullet->body->GetPosition();
            bullet->body->SetTransform({bulletPos.x + cos(angle) * 0.005f, bulletPos.y + sin(angle) * 0.005f}, angle);
        }
    }
}

void Level::update() {
    checkBullets();
    checkShooting();
    checkDeaths();
    world->Step(0.1, 10, 10);
}

void Level::deleteBullet(Bullet* bullet) const {
    objects->erase(find(objects->begin(), objects->end(), bullet));
    bullets->erase(find(bullets->begin(), bullets->end(), bullet));
    delete bullet;
}

void Level::checkBullets() const {

    for (Bullet* bullet : *bullets) {

        if (bullet->lifetime <= 0) {
            deleteBullet(bullet);
            continue;
        }

        for (Entity* entity : *entities) {
            if (Level::collide(bullet, entity)) {
                entity->dealDamage(bullet->damage);
                deleteBullet(bullet);
                break;
            }
        }

        for (PhysicalObject* object : *objects) {
            if (object->body->IsBullet())
                continue;

            if (Level::collide(bullet, object)) {
                deleteBullet(bullet);
                break;
            }
        }
    }
}

Weapon Level::getPistol() const {
    Weapon weapon (Pistol::power, Pistol::damage, Pistol::reload, Pistol::rate, Pistol::accuracy, Pistol::recoil, Pistol::bullet_size, Pistol::capacity, Animator(), Animator());
    weapon.weaponAnimator->createAnimation("idle", {(*textures)["pistol_texture"]}, 10);
    weapon.bulletAnimator.createAnimation("flying", {(*textures)["pistol_bullet_frame1_texture"], (*textures)["pistol_bullet_frame2_texture"]}, 1);
    return weapon;
}

void Level::loadDefaultTextures() const {
    for (const auto& name_path : default_textures) {
        sf::Texture* texture = loadTexture(name_path.first, name_path.second);
        (*textures)[name_path.first] = texture;
    }
}

Level::~Level() {
    for (PhysicalObject* object : *objects) {
        delete object;
    }
    delete objects;
    for (Entity* entity : *entities) {
        delete entity;
    }
    delete entities;
    for (const auto& texture : *textures) {
        delete texture.second;
    }
    delete textures;
    for (const auto& font : *fonts) {
        delete font.second;
    }
    delete fonts;
    delete bullets;
    delete view;
    delete world;
    delete window;
}

bool Level::collide(PhysicalObject* obj1, PhysicalObject* obj2) {

    b2Vec2 pos1 = obj1->body->GetPosition();
    sf::Vector2f size1 = obj1->size;

    b2Vec2 pos2 = obj2->body->GetPosition();
    sf::Vector2f size2 = obj2->size;

    float inaccuracy = 0.15;

    return abs(pos1.x - pos2.x) - inaccuracy < (size1.x + size2.x) && abs(pos1.y - pos2.y) - inaccuracy < (size1.y + size2.y);
}

void Level::movePlayerCamera() const {
    if (player == nullptr)
        return;

    b2Vec2 pos = player->body->GetPosition();
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    float x = ((mousePos.x - window->getSize().x * 0.5f) * h + pos.x * zoom - view->getCenter().x);
    float y = ((mousePos.y - window->getSize().y * 0.5f) * h + pos.y * zoom + camera_offset_y - view->getCenter().y);
    view->move(pow(x * n * r, 3), y * n * 0.6);
}

sf::Font *Level::loadFont(const std::string& name, const std::string& path) const {
    auto* font = new sf::Font();

    if (!font->loadFromFile(path)) {
        std::cout << "file not found" << '\n';
        return nullptr;
    }

    (*fonts)[name] = font;

    return font;
}

void Level::loadDefaultFonts() const {
    for (const auto& name_path : default_fonts) {
        sf::Font* font = loadFont(name_path.first, name_path.second);
        (*fonts)[name_path.first] = font;
    }
}

void Level::start() {
    uint quiting = 0;

    while (window->isOpen())
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                stop();
                return;
            }
        }
        window->clear(sf::Color::White);

        for (PhysicalObject* object : *objects) {
            object->update();
            window->draw(*object->shape);
            window->draw(*object->animator->sprite);
        }
        for (Entity* entity : *entities) {
            if (entity == player)
                entity->weapon->angle = getMouseToEntityAngle(entity);
            entity->update();
            window->draw(*entity->shape);
            window->draw(*entity->animator->sprite);
            window->draw(*entity->weapon->weaponAnimator->sprite);
            displayEntityInfo(entity);
        }
        if (player == nullptr)
            gameover();
        else
            displayPlayerInfo();

        update();

        window->setView(*view);

        window->display();

        movePlayerCamera();

        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) ? quiting++ : quiting = 0;

        if (quiting >= quiting_time) {
            stop();
            return;
        }
    }
}

void Level::gameover() const {
    sf::Text gameoverText;
    uint text_size = 200;

    gameoverText.setFont(*(*fonts)["default_font"]);
    gameoverText.setString("Game Over");
    gameoverText.setCharacterSize(text_size);
    gameoverText.setFillColor(sf::Color::Black);
    gameoverText.setStyle(sf::Text::Bold);

    sf::Vector2f pos = view->getCenter();
    pos.x -= text_size * 0.5f;
    pos.y -= text_size * 0.5f;

    gameoverText.setPosition({pos.x, pos.y});

    window->draw(gameoverText);
}

void Level::stop() {
    window->close();
    delete this;
}

void Level::displayPlayerInfo() const {
    if (player == nullptr)
        return;

    uint text_size = 100;

    sf::Text healthText;

    healthText.setFont(*(*fonts)["default_font"]);
    healthText.setString(std::to_string(player->health));
    healthText.setCharacterSize(text_size);
    healthText.setFillColor(sf::Color::Red);
    healthText.setStyle(sf::Text::Bold);

    sf::Vector2f healthPos = view->getCenter();
    healthPos.x -= view->getSize().x * 0.5f - playerHealthPos.x;
    healthPos.y -= view->getSize().y * 0.5f - playerHealthPos.y;

    healthText.setPosition({healthPos.x, healthPos.y});

    window->draw(healthText);

    sf::Text ammoText;

    ammoText.setFont(*(*fonts)["default_font"]);
    ammoText.setString(std::to_string(player->weapon->ammo));
    ammoText.setCharacterSize(text_size);
    ammoText.setFillColor(sf::Color::Yellow);
    ammoText.setStyle(sf::Text::Bold);

    sf::Vector2f ammoPos = view->getCenter();
    ammoPos.x -= view->getSize().x * 0.5f - playerAmmoPos.x;
    ammoPos.y -= view->getSize().y * 0.5f - playerAmmoPos.y;

    ammoText.setPosition({ammoPos.x, ammoPos.y});

    window->draw(ammoText);
}

void Level::displayEntityInfo(Entity* entity) const {
    if (entity == player)
        return;

    sf::Text healthText;
    uint text_size = 32;
    uint offset_x = 0;
    uint offset_y = 3;

    healthText.setFont(*(*fonts)["default_font"]);
    healthText.setString(std::to_string(entity->health));
    healthText.setCharacterSize(text_size);
    healthText.setFillColor(sf::Color::Red);
    healthText.setStyle(sf::Text::Bold);

    b2Vec2 pos = entity->body->GetPosition();
    pos.x = pos.x * zoom - entity->size.x * zoom * 0.5f - offset_x;
    pos.y = pos.y * zoom - entity->size.y * zoom - text_size - offset_y;
    healthText.setPosition({pos.x, pos.y});

    window->draw(healthText);
}

void Level::checkDeaths() {
    for (Entity* entity : *entities) {
        if (!entity->isDead())
            return;

        if (entity == player) {
            player = nullptr;
            gameover();
        }

        deleteEntity(entity);
    }
}

void Level::deleteEntity(Entity* entity) const {
    entities->erase(find(entities->begin(), entities->end(), entity));
    delete entity;
}

sf::Vector2f Level::getMouseGlobalPosition() const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    mousePos.x -= window->getSize().x * 0.5f;
    mousePos.y -= window->getSize().y * 0.5f;
    sf::Vector2f viewPos = view->getCenter();
    sf::Vector2f pos(viewPos.x + mousePos.x, viewPos.y + mousePos.y);
    return pos;
}

float Level::getMouseToEntityAngle(Entity* entity) const {
    b2Vec2 entityPos = entity->body->GetPosition();
    sf::Vector2f pos = getMouseGlobalPosition();
    float angle = atan2(pos.y / zoom - entityPos.y, pos.x / zoom - entityPos.x) + 360 * DEGTORAD;
    return angle;
}
