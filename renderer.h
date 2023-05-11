#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "Level.h"
#include "Animator.h"

const float timeStep = 0.001f;

void render(sf::RenderWindow*, Level*);

void render(sf::RenderWindow*, Level*, Animator*);
