#include "helpers.h"


bool can_go(int x, int y){
    return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
}
bool in_interval(int x, int a, int b){
    return x >= a-b && x <= a+b;
}
float distance(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
