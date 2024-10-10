#pragma once

#include "MovingObject.hpp"
#include "Ghost.hpp"
#include <utility>

std::pair<int, int> random_target(Ghost &obj);
std::pair<int, int> pinky_target(MovingObject &pacman, Ghost &l);
std::pair<int, int> inky_target(MovingObject &pacman, Ghost &blinky);
std::pair<int, int> clyde_target(MovingObject &pacman, Ghost &clyde);

