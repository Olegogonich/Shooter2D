cmake_minimum_required(VERSION 3.21)
project(Shooter2D)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(box2d REQUIRED)

include_directories(resources/SFML/include resources/box2d-main/include/box2d)

add_executable(Shooter2D main.cpp Level.cpp Level.h PhysicalObject.cpp PhysicalObject.h Player.cpp Player.h Animator.cpp Animator.h Animation.cpp Animation.h Controls.cpp Controls.h Constants.h Bullet.cpp Bullet.h Pistol.h Weapon.cpp Weapon.h Entity.cpp Entity.h)

target_link_libraries(Shooter2D sfml-graphics sfml-audio box2d::box2d)