#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <stdexcept>

#include "Settings.h"
#include "Coin.hpp"

sf::Texture build_map(sf::Texture &atlasTexture);
std::vector<Coin> make_coins();
std::vector<POWER_UP> make_power();
