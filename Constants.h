#pragma once
#include <map>
#include <box2d/b2_body.h>
#include <SFML/System/Vector2.hpp>

const float zoom = 135.f;
const float antizoom = 4.f;
const float DEGTORAD = 0.0174532925199432957f;
const float RADTODEG = 57.295779513082320876f;

const sf::Vector2f playerHealthPos {10, 10};
const sf::Vector2f playerAmmoPos {10, 120};

const uint quiting_time = 60;
const uint bullet_lifetime = 100;
const uint player_max_health = 1;
const bool dynamic_bullets = true;

const std::map<std::string, std::string> default_fonts {
        std::pair<std::string, std::string>("default_font",                 "/Users/oleh/CLionProjects/Shooter2D/resources/fonts/square-deal.ttf")
};
const std::map<std::string, std::string> default_textures {
        std::pair<std::string, std::string>("pistol_texture",               "/Users/oleh/CLionProjects/Shooter2D/resources/images/pic.jpg"),
        std::pair<std::string, std::string>("pistol_bullet_frame1_texture", "/Users/oleh/CLionProjects/Shooter2D/resources/images/man0.png"),
        std::pair<std::string, std::string>("pistol_bullet_frame2_texture", "/Users/oleh/CLionProjects/Shooter2D/resources/images/man1.png"),
        std::pair<std::string, std::string>("player_texture",               "/Users/oleh/CLionProjects/Shooter2D/resources/images/pic.jpg"),
};

const b2BodyType bullet_body_type = dynamic_bullets ? b2_dynamicBody : b2_kinematicBody;
