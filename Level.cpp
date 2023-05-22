#include "Level.h"

Level::Level(const b2Vec2& gravity, sf::RenderWindow *window) :
    fonts(new std::map<std::string, sf::Font*>()),
    textures(new std::map<std::string, sf::Texture*>()),
    objects(new std::vector<PhysicalObject*>()),
    entities(new std::vector<Entity*>()),
    effects(new std::vector<Vfx*>()),
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

Bullet* Level::createBullet(const sf::Vector2f& pos, const sf::Vector2f& size, const uint& damage, const float& angle, const float& power, const float& mass, const Animator& animator) const {
    auto* object = new Bullet(*this->world, pos, size, damage, angle, power, mass, animator);
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
                entity->weapon->bullet_mass,
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
    Weapon weapon (Pistol::power, Pistol::bullet_mass, Pistol::damage, Pistol::reload, Pistol::rate, Pistol::accuracy, Pistol::recoil, Pistol::bullet_size, Pistol::capacity, Animator(), Animator());
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
    for (Vfx* vfx : *effects) {
        delete vfx;
    }
    delete effects;
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
    uint quitingTextAlpha;
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

        displayObjects();
        displayEntities();
        displayEffects();

        if (player == nullptr)
            gameover();
        else
            displayPlayerInfo();

        quitingTextAlpha = 255.f / quiting_time * quiting;
        displayText("quiting...", {10, (uint)view->getSize().y - 35}, 50, sf::Color(220, 220, 220, quitingTextAlpha), sf::Color(0, 0, 0, quitingTextAlpha), 1);

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
    uint size = 225;
    sf::Vector2u pos = {0, 0};
    sf::Color color(70, 70, 70);
    sf::Color outline(80, 80, 80);
    displayText("Game Over", pos, size, color, outline, 5);
}

void Level::stop() {
    window->close();
    delete this;
}

void Level::displayPlayerInfo() const {
    if (player == nullptr)
        return;

    sf::Color health_color (255, 127, 127);
    sf::Color health_outline_color (200, 100, 100);
    displayText(std::to_string(player->health), playerHealthPos, playerInfoSize, health_color, health_outline_color, 3);

    sf::Color ammo_color (250, 250, 10);
    sf::Color ammo_outline_color (205, 205, 100);
    displayText(std::to_string(player->weapon->ammo), playerAmmoPos, playerInfoSize, ammo_color, ammo_outline_color, 3);
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
    healthText.setFillColor(sf::Color(255, 127, 127));
    healthText.setOutlineColor(sf::Color(200, 100, 100));
    healthText.setOutlineThickness(2);
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

void Level::displayText(const std::string &string, const sf::Vector2u &pos, const uint& size, const sf::Color &color) const {
    sf::Text text;
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    displayText(text, pos);
}

void Level::displayText(const std::string &string, const sf::Vector2u &pos, const uint& size, const sf::Color &color, const sf::Color &outlineColor, const float& outlineThickness) const {
    sf::Text text;
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(outlineThickness);
    displayText(text, pos);
}

void Level::displayText(sf::Text text, const sf::Vector2u& pos) const {

    text.setFont(*(*fonts)["default_font"]);

    text.setStyle(sf::Text::Bold);

    sf::Vector2f textPos = view->getCenter();
    textPos.x -= view->getSize().x * 0.5f - pos.x;
    textPos.y -= (view->getSize().y + text.getCharacterSize()) * 0.5f - pos.y;

    text.setPosition({textPos.x, textPos.y});

    window->draw(text);
}

void Level::displayObjects() const {
    for (PhysicalObject* object : *objects) {
        object->update();
        window->draw(*object->shape);
        window->draw(*object->animator->sprite);
    }
}

void Level::displayEntities() const {
    for (Entity* entity : *entities) {
        if (entity == player)
            entity->weapon->angle = getMouseToEntityAngle(entity);
        entity->update();
        window->draw(*entity->shape);
        window->draw(*entity->animator->sprite);
        window->draw(*entity->weapon->weaponAnimator->sprite);
        displayEntityInfo(entity);
    }
}

void Level::displayEffects() const {
    for (Vfx* vfx : *effects) {
        vfx->update();
        window->draw(*vfx->sprite);
    }
}

Vfx* Level::createVfx(const Animation &animation, const sf::Vector2f &pos, const sf::Vector2f &size, const float &angle, const bool &cycle, const bool &stopAtLast) const {
    auto* vfx = new Vfx(animation, pos, size, angle, cycle, stopAtLast);
    effects->push_back(vfx);
    return vfx;
}


