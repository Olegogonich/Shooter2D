#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "Level.h"

void render(Level*);

void movePlayerCamera(sf::View&, Player&, sf::Window&);