//#ifndef Settings_H
//#define Settings_H
#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>

#define INFTY INT_MAX
#define POWER_UP Coin

constexpr int MAP_WIDTH = 28;
constexpr int MAP_HEIGHT = 27;
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;
constexpr float VELOCITY = 0.0011;
constexpr int POS_DIV = 2;

const int width_ratio = SCREEN_WIDTH / MAP_WIDTH;
const int height_ratio = SCREEN_HEIGHT / MAP_HEIGHT;
const float TIME_SPEED = 7000.0f;

// Sample map, in theory should be done using a maze generator (the prim's one should be good for this)
extern int pacman_map[MAP_HEIGHT][MAP_WIDTH];

//#endif // !Settings_H


void loadMap(std::string mapFile);
