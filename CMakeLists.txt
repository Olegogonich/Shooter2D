cmake_minimum_required(VERSION 3.21)
project(Shooter2D)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(box2d REQUIRED)

include_directories(SFML/include box2d-main/include/box2d)

add_executable(Shooter2D main.cpp renderer.cpp renderer.h Level.cpp Level.h GameObject.cpp GameObject.h Player.cpp Player.h Animator.cpp Animator.h Animation.cpp Animation.h)

target_link_libraries(Shooter2D sfml-graphics sfml-audio box2d::box2d)