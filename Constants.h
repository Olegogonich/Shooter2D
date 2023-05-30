#pragma once
#include <map>
#include <box2d.h>
#include <SFML/System/Vector2.hpp>

const float zoom = 135.f;
const float antizoom = 4.f;
const float DEGTORAD = 0.0174532925199432957f;
const float RADTODEG = 57.295779513082320876f;

const b2Vec2 gravity(0.0f, 2.f);

const sf::Vector2u playerHealthPos {20, 50};
const sf::Vector2u playerAmmoPos {20, 150};
const uint playerInfoSize = 100;

const uint quiting_time = 60;
const uint bullet_lifetime = 15;
const uint player_max_health = 10;
const uint enemy_max_health = 10;
const bool dynamic_bullets = true;

const std::string first_level_path = "resources/levels/first.lvl";
const std::string second_level_path = "resources/levels/second.lvl";
const std::string third_level_path = "resources/levels/third.lvl";



const std::map<std::string, std::string> default_fonts {
        std::pair<std::string, std::string>("default_font",                 "resources/fonts/square-deal.ttf")
};

const b2BodyType bullet_body_type = dynamic_bullets ? b2_dynamicBody : b2_kinematicBody;
