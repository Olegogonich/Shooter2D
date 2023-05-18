#pragma once
#include <map>

const float zoom = 100.f;
const float antizoom = 3.f;
const float DEGTORAD = 0.0174532925199432957f;
const float RADTODEG = 57.295779513082320876f;
const float bullet_lifetime = -1;

const std::map<std::string, std::string> default_textures {
        std::pair<std::string, std::string>("pistol_texture",               "/Users/oleh/CLionProjects/Shooter2D/resources/images/pic.jpg"),
        std::pair<std::string, std::string>("pistol_bullet_frame1_texture", "/Users/oleh/CLionProjects/Shooter2D/resources/images/man0.png"),
        std::pair<std::string, std::string>("pistol_bullet_frame2_texture", "/Users/oleh/CLionProjects/Shooter2D/resources/images/man1.png"),
        std::pair<std::string, std::string>("player_texture",               "/Users/oleh/CLionProjects/Shooter2D/resources/images/pic.jpg"),
};