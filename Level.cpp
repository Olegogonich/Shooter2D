#include "Level.h"

Level::Level(const b2Vec2& gravity, sf::RenderWindow *window) :
    textures(new std::map<std::string, sf::Texture*>()),
    objects(new std::vector<PhysicalObject*>()),
    bullets(new std::vector<Bullet*>()),
    view(new sf::View(window->getDefaultView())),
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
    float angle = atan2(pos.y / zoom - playerPos.y, pos.x / zoom - playerPos.x) + 360 * DEGTORAD;

    Bullet* bullet = createBullet(
        {
             playerPos.x * antizoom,
             playerPos.y * antizoom
        },
        {
            player->weapon->bullet_size,
            player->weapon->bullet_size
        },
        angle,
        player->weapon->power,
        *player->weapon->bulletAnimator
    );

    b2Vec2 bulletPos;
    while (Level::collide(bullet, player)) {
        bulletPos = bullet->body->GetPosition();
        bullet->body->SetTransform({bulletPos.x + cos(angle) * 0.01f, bulletPos.y + sin(angle) * 0.01f}, angle);
    }
}

void Level::update() const {
    checkBullets();
    checkPlayerShooting();
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

    Animator weaponAnimator = Animator::newStaticTexture((*textures)["pistol_texture"]);
    Animator bulletAnimator;
    bulletAnimator.createAnimation("flying", {(*textures)["pistol_bullet_frame1_texture"], (*textures)["pistol_bullet_frame2_texture"]}, 1);

    return {Pistol::power, Pistol::reload, Pistol::rate, Pistol::accuracy, Pistol::recoil, Pistol::bullet_size, Pistol::capacity, weaponAnimator, bulletAnimator};
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

Level::~Level() {
    for (PhysicalObject* object : *objects) {
        delete object;
    }
    delete objects;
    for (const auto& texture : *textures) {
        delete texture.second;
    }
    delete textures;
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

    float inaccuracy = 0.2;

    return abs(pos1.x - pos2.x) - inaccuracy < (size1.x + size2.x) && abs(pos1.y - pos2.y) - inaccuracy < (size1.y + size2.y);
}

