#include "Weapon.h"

Weapon::Weapon(float power, uint damage, float reload, float rate, float accuracy, float recoil, float bulletSize, uint capacity, const Animator& weaponAnimator, const Animator& bulletAnimator) :
        angle(0), power(power), damage(damage), reload_time(reload), rate(rate), accuracy(accuracy), recoil(recoil),
        bullet_size(bulletSize), capacity(capacity),ammo(capacity), weaponAnimator(new Animator(weaponAnimator)),
        bulletAnimator(bulletAnimator) { }

Weapon::Weapon(const Weapon& temp) :
        angle(temp.angle), power(temp.power), damage(temp.damage), reload_time(temp.reload_time), rate(temp.rate),
        accuracy(temp.accuracy), recoil(temp.recoil), bullet_size(temp.bullet_size), capacity(temp.capacity),
        ammo(temp.capacity), weaponAnimator(new Animator(*temp.weaponAnimator)), bulletAnimator(temp.bulletAnimator) { }

Weapon::~Weapon() {
    delete weaponAnimator;
}
