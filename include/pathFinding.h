#pragma once

#include <utility>
#include "Settings.h"
#include <queue>

std::pair<int, int> BFS(int map[][MAP_WIDTH], std::pair<int, int> start, std::pair<int, int> end);
bool is_possible(std::pair<int, int> p);
std::pair<int, int> nearest_move(std::pair<int, int> obj);
