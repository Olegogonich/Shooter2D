#include "Enemy.h"
#include <random>
#include <ctime>

Enemy::Enemy(b2World& world ,const sf::Vector2f& pos, const sf::Vector2f& size, const Animator& _animator)
    : Entity(world, pos, size, _animator, enemy_max_health, JUMP_FORCE, TOP_SPEED, ACCELERATION, FRICTION) {
    target = nullptr;
    aimingAngle = 0;
    std::srand(std::time(nullptr));
    chasing_range += std::rand() % (int)range;
}

void Enemy::update() {
    Entity::update();
    checkAmmo();
    aim();
    chase();

    if (isOnFloor())
        stop();
}

void Enemy::aim() {
    direction = (aimingAngle < -90 * DEGTORAD || aimingAngle > 90 * DEGTORAD) ? LEFT : RIGHT;

    if (target == nullptr) {
        aimPos = body->GetPosition();
        aimPos.x += direction == RIGHT ? 10 : -10;
    } else {
        aimPos = target->body->GetPosition();
    }

    b2Vec2 pos = aimPos - body->GetPosition();
    float targetAngle = atan2(pos.y, pos.x);

    aimingAngle += (targetAngle - aimingAngle) * aiming_speed;

    if (target != nullptr && abs(aimingAngle - targetAngle) < min_angle_for_shooting * DEGTORAD)
        shoot();
}

void Enemy::checkAmmo() {
    if (weapon->ammo > 0)
        return;

    reload();
}

void Enemy::setTarget(Entity* _target) {
    target = _target;
}

void Enemy::resetTarget() {
    target = nullptr;
}

void Enemy::chase() {
    animator->currentAnimation = "idle";

    if (target == nullptr)
        return;

    b2Vec2 pos = target->body->GetPosition() - body->GetPosition();
    b2Vec2 pos1 = pos;
    pos1.x += chasing_range / antizoom;
    b2Vec2 pos2 = pos;
    pos2.x -= chasing_range / antizoom;

    if (pos.x > attack_radius || pos.y > attack_radius)
        return;

    if (round(pos1.x) == 0 || round(pos2.x) == 0)
        return;

    if (abs(body->GetPosition().x - pos1.x) < abs(body->GetPosition().x - pos2.x))
        if(pos1.x > 0) {
            moveRight();
            animator->currentAnimation = "running_right";
        } else {
            moveLeft();
            animator->currentAnimation = "running_left";
        }
    else
        pos2.x > 0 ? moveRight() : moveLeft();
}

Enemy::~Enemy() = default;
