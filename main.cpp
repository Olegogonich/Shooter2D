#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Animator.h"
#include "Controls.h"

int main() {
//
//    Player* player = level->createPlayer({0, 0}, {1, 2}, Animator(), getDefaultControls());
//    player->animator->createAnimation("dead", {(*level->textures)["pistol_texture"]}, 100);
//    player->animator->createAnimation("running", {(*level->textures)["pistol_bullet_frame1_texture"], (*level->textures)["pistol_bullet_frame2_texture"]}, 10);
//    player->animator->createAnimation("idle", {(*level->textures)["pistol_bullet_frame1_texture"]}, 1);
//    player->setWeapon(level->getPistol());
//
//    Enemy* enemy = level->createEnemy({10, -10}, {1, 2}, Animator());
//    enemy->animator->createAnimation("dead", {(*level->textures)["pistol_texture"]}, 100);
//    enemy->animator->createAnimation("running", {(*level->textures)["pistol_bullet_frame1_texture"], (*level->textures)["pistol_bullet_frame2_texture"]}, 10);
//    enemy->animator->createAnimation("idle", {(*level->textures)["pistol_bullet_frame1_texture"]}, 1);
//    enemy->setWeapon(level->getPistol());
//
//    Animator staticAnimator = Animator::newStaticTexture((*level->textures)["pistol_texture"]);
//    level->createStatic({-70, 25}, {200, 3}, staticAnimator);
//    level->createStatic({30, 17}, {4, 4}, staticAnimator);
//    level->createStatic({18, 18.5}, {1.2, 1}, staticAnimator);
//    level->createStatic({24, 17.25}, {1.2, 1}, staticAnimator);
//    level->createStatic({36, 20}, {1.2, 1}, staticAnimator);
//    level->createStatic({42, 16.5}, {1.2, 1}, staticAnimator);
//    level->createStatic({10, 14}, {3, 1}, staticAnimator);
//    level->createDynamic({-10, 0}, {3, 3}, staticAnimator);
    auto game = new Game();
    game->start();

    game->stop();

    return 0;
}
