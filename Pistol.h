#pragma once
#include <iostream>
#include <vector>
#include "Animator.h"
#include "Weapon.h"
#include "Constants.h"

struct Pistol {

    constexpr static float power = 15;
    constexpr static float bullet_mass = 0.01;
    constexpr static uint damage = 1;
    constexpr static float reload = 100;
    constexpr static float rate = 10;
    constexpr static float stability = 0.1;
    constexpr static float recoil = 10;
    constexpr static float max_recoil = 50;
    constexpr static float bullet_size = 0.1;
    constexpr static uint capacity = 15;
};
