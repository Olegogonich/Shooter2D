#pragma once
#include "Animator.h"

struct Weapon {
    float power;
    float bullet_mass;
    uint damage;
    float reload_time;
    float rate;
    float stability;
    float recoil;
    float current_recoil;
    float max_recoil;
    float bullet_size;
    uint capacity;
    float angle;

    uint ammo;

    Animator* weaponAnimator;
    Animator bulletAnimator;

    Weapon(float, float, uint, float, float, float, float, float, float, uint, const Animator&, const Animator&);

    Weapon(const Weapon&);

    ~Weapon();
};
