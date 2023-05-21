#pragma once
#include "Animator.h"

struct Weapon {
    float power;
    float reload_time;
    float rate;
    float accuracy;
    float recoil;
    float bullet_size;
    uint capacity;

    uint ammo;

    Animator* weaponAnimator;
    Animator* bulletAnimator;

    Weapon(float, float,float, float, float, float, uint, const Animator&, const Animator&);

    ~Weapon();
};
