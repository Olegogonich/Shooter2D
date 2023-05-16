#include "Level.h"

Level::Level(const b2Vec2& gravity, sf::RenderWindow *window) :
    textures(new std::map<std::string, sf::Texture*>()),
    objects(new std::vector<PhysicalObject*>()),
    bullets(new std::vector<Bullet*>()),
    world(new b2World(gravity)),
    window(window)
    { loadDefaultTextures(); }

PhysicalObject* Level::createObject(const b2BodyType& type, const sf::Vector2f& pos, const sf::Vector2f& size, const Animator &animator) const {
    auto* object = new PhysicalObject(*this->world, type, pos, size, animator);
    objects->push_back(object);
    return object;
}

PhysicalObject* Level::createObject(const b2BodyType& type, const sf::Vector2f& pos, const sf::Vector2f& size, sf::Texture* texture) const {
    auto* object = new PhysicalObject(*this->world, type, pos, size, texture);
    objects->push_back(object);
    return object;
}

Player* Level::createPlayer(const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& animator, const Controls& controls) {
    auto* object = new Player(*this->world, pos, size, animator, controls);
    objects->push_back(object);
    player = object;
    return object;
}

StaticObject* Level::createStatic(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Texture* texture) const {
    auto* object = new StaticObject(*this->world, pos, size, texture);
    objects->push_back(object);
    return object;
}

Bullet* Level::createBullet(const sf::Vector2f& pos, const sf::Vector2f& size, const float& angle, const float& power, sf::Texture* texture) const {
    auto* object = new Bullet(*this->world, pos, size, angle, power, texture);
    objects->push_back(object);
    bullets->push_back(object);
    return object;
}

Bullet* Level::createBullet(const sf::Vector2f& pos, const sf::Vector2f& size, const float& angle, const float& power, const Animator& animator) const {
    auto* object = new Bullet(*this->world, pos, size, angle, power, animator);
    objects->push_back(object);
    bullets->push_back(object);
    return object;
}

sf::Texture* Level::loadTexture(const std::string& name, const std::string& path) const {
     auto* texture = new sf::Texture();

    if (!texture->loadFromFile(path)) {
        std::cout << "file not found" << '\n';
    }
    texture->setSmooth(true);
    (*textures)[name] = texture;

    return texture;
}

void Level::checkPlayerShooting() const {
    if (player->weapon == nullptr || !player->shoot())
        return;

    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    mousePos.x -= window->getSize().x * 0.5f;
    mousePos.y -= window->getSize().y * 0.5f;
    b2Vec2 playerPos = player->body->GetPosition();
    sf::Vector2f viewPos = view->getCenter();
    sf::Vector2f pos (viewPos.x + mousePos.x, viewPos.y + mousePos.y);

    std::cout << "created bullet - " << createBullet(
        {
             playerPos.x * antizoom,
             playerPos.y * antizoom
        },
        {
            player->weapon->bullet_size,
            player->weapon->bullet_size
        },
        atan2(pos.y / zoom - playerPos.y, pos.x / zoom - playerPos.x) + 360 * DEGTORAD,
        player->weapon->power,
        *player->weapon->bulletAnimator
    ) << '\n';

}

void Level::update() const {
    checkPlayerShooting();
    checkBullets();
    world->Step(0.1, 10, 10);
}

void Level::checkBullets() const {
    for (Bullet* bullet : *bullets) {
        if (bullet->body->GetContactList() == nullptr || bullet->body->GetContactList()->other->IsBullet())
            continue;

        objects->erase(find(objects->begin(), objects->end(), bullet));
        bullets->erase(find(bullets->begin(), bullets->end(), bullet));
        std::cout << "deleted bullet - " << bullet << '\n';
        delete bullet;
    }
}

Weapon Level::getPistol() const {

    Animator weaponAnimator = Animator::newStaticTexture((*textures)["pistol_texture"]);
    Animator bulletAnimator;
    bulletAnimator.createAnimation("flying", {(*textures)["pistol_bullet_frame1_texture"], (*textures)["pistol_bullet_frame2_texture"]}, 1);

    return {Pistol::power, Pistol::reload, Pistol::rate, Pistol::accuracy, Pistol::recoil, Pistol::bullet_size, Pistol::capacity, weaponAnimator, bulletAnimator};
}

Level::~Level() {
    for (PhysicalObject* object : *objects) {
        delete object;
    }
    delete objects;
    for (const auto& texture : *textures) {
        delete texture.second;
    }
    delete textures;
    delete view;
    delete bullets;
    delete world;
    delete window;
}

void Level::loadDefaultTextures() const {
    for (const auto& name_path : default_textures) {
        auto* texture = new sf::Texture();

        if (!texture->loadFromFile(name_path.second)) {
            std::cout << "Can't load file: \"" + name_path.second + "\"";
            continue;
        }

        (*textures)[name_path.first] = texture;
    }
}

