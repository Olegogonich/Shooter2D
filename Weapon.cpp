#include "Weapon.h"

Weapon::Weapon(
        float power,
        uint damage,
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
        damage(damage),
        reload_time(reload),
        rate(rate),
        accuracy(accuracy),
        recoil(recoil),
        bullet_size(bulletSize),
        capacity(capacity),
        ammo(capacity),
        weaponAnimator(weaponAnimator),
        bulletAnimator(bulletAnimator)
        { }
