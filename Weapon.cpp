#include "Weapon.h"

Weapon::Weapon(float power, float bulletMass, uint damage, float reload, float rate, float accuracy, float recoil, float max_recoil, float bulletSize, uint capacity, const Animator& weaponAnimator, const Animator& bulletAnimator) :
        angle(0), current_recoil(0), power(power), bullet_mass(bulletMass), damage(damage), reload_time(reload),
        rate(rate), stability(accuracy), recoil(recoil), max_recoil(max_recoil), bullet_size(bulletSize),
        capacity(capacity), ammo(capacity), weaponAnimator(new Animator(weaponAnimator)), bulletAnimator(bulletAnimator) { }

Weapon::Weapon(const Weapon& temp) :
        angle(temp.angle), bullet_mass(temp.bullet_mass), power(temp.power), damage(temp.damage),
        reload_time(temp.reload_time), rate(temp.rate), stability(temp.stability), recoil(temp.recoil),
        max_recoil(temp.max_recoil),
        bullet_size(temp.bullet_size), capacity(temp.capacity), ammo(temp.capacity),
        weaponAnimator(new Animator(*temp.weaponAnimator)), bulletAnimator(temp.bulletAnimator) { }

Weapon::~Weapon() {
    delete weaponAnimator;
}
