#pragma once
#include <iostream>
#include <vector>
#include "Animator.h"
#include "Weapon.h"

struct Pistol {

    constexpr static float power = 5;
    constexpr static float damage = 1;
    constexpr static float reload = 100;
    constexpr static float rate = 10;
    constexpr static float accuracy = 0.8;
    constexpr static float recoil = 1;
    constexpr static float bullet_size = 0.1;
    constexpr static uint capacity = 10;
};
