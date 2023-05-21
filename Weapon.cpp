#include "Weapon.h"

Weapon::Weapon(
        float power,
        float reload,
        float rate,
        float accuracy,
        float recoil,
        float bulletSize,
        uint capacity,
        const Animator& weaponAnimator,
        const Animator& bulletAnimator
        ):
        power(power),
        reload_time(reload),
        rate(rate),
        accuracy(accuracy),
        recoil(recoil),
        bullet_size(bulletSize),
        capacity(capacity),
        ammo(capacity),
        weaponAnimator(new Animator(weaponAnimator)),
        bulletAnimator(new Animator(weaponAnimator))
        { }

Weapon::~Weapon() {
    delete weaponAnimator;
}
