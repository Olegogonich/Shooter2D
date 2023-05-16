#pragma once
#include <iostream>
#include <vector>
#include "Animator.h"
#include "Weapon.h"

struct Pistol {

    constexpr const static float power = 3;
    constexpr static float reload = 100;
    constexpr static float rate = 10;
    constexpr static float accuracy = 0.8;
    constexpr static float recoil = 1;
    constexpr static float bullet_size = 0.2;
    constexpr static uint capacity = 10;
};
