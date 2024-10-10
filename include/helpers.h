#pragma once

#include "Settings.h"
#include <cmath>
struct Target{
    int d = 0;
    // 0 = up/down 1 = right/left
    int where = -1;
    bool is_finished = true;
    bool init = false;
};

bool can_go(int x, int y);
bool in_interval(int x, int a, int b);
float distance(int x1, int y1, int x2, int y2);
