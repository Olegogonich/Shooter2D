#include <vector>
#include "Animator.h"

struct Vfx {
    sf::Vector2f size;
    float angle;
    Animator* animator;
    bool cycle;
    bool stopAtLast;

    void update() const;

    Vfx(const Animator&, const sf::Vector2f& size, const float& angle, const bool&, const bool&);

    Vfx(const Vfx&);

    ~Vfx();
};

