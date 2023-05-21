#include "Player.h"

Player::Player(b2World& world ,const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& _animator, const Controls& _controls)
: Entity(world, pos, size, _animator, player_max_health, JUMP_FORCE, TOP_SPEED, ACCELERATION, FRICTION) {
    controls = new Controls(_controls);
    cannotShoot = 0;
    body->SetFixedRotation(true);
}

void Player::update() {
    Entity::update();
    control();
}

void Player::control() {
    animator->currentAnimation = "idle";

    bool jumped = controls->jumpPressed() && isOnFloor();
    bool movedRight = controls->rightPressed();
    bool movedLeft = controls->leftPressed();
    bool shooted = controls->shootPressed();
    bool reloaded = controls->reloadPressed();

    if (weapon != nullptr)
        std::cout << " health: " << health << " shoot pressed: " <<  shooted << " ammo: " << weapon->ammo << " reloading: " << reloading << '\r';

    if (jumped) {
        jump();
    }
    if (movedRight) {
        moveRight();
        animator->currentAnimation = "running";
    }
    if (movedLeft) {
        moveLeft();
        animator->currentAnimation = "running";
    }

    if (!movedRight && !movedLeft) {
        stop();
    }

    if (shooted) {
        shoot();
    }

    if (reloaded) {
        reload();
    }
}

Player::~Player() {
    delete controls;
    delete weapon;
}
