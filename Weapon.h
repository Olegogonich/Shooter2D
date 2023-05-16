#pragma once
#include "Animator.h"

struct Weapon {
    float power;
    float reload;
    float rate;
    float accuracy;
    float recoil;
    float bullet_size;
    uint capacity;
    Animator* weaponAnimator;
    Animator* bulletAnimator;

    Weapon(float, float,float, float, float, float, uint, const Animator&, const Animator&);

    ~Weapon();
};
