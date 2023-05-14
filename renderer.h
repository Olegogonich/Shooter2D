#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "Level.h"
#include "Animator.h"

void render(sf::RenderWindow*, Level*);

void movePlayerCamera(sf::View&, Player*, sf::Window*);