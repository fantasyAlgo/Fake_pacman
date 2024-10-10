#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Settings.h"
#include "Coin.hpp"

std::vector<sf::RectangleShape> build_map();
std::vector<Coin> make_coins();
std::vector<POWER_UP> make_power();
