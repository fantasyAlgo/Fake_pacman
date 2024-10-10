#include "ghost_mov.hpp"



std::pair<int, int> random_target(Ghost &obj){
    std::pair<int, int> p = {obj.getPosition().x/width_ratio, obj.getPosition().y/height_ratio};
    p.first = p.first + (rand()%3)-1;
    p.second = p.second + (rand()%3)-1;
    if (pacman_map[p.second][p.first] == 1)
        return nearest_move(p);
    return p;
}


std::pair<int, int> pinky_target(MovingObject &pacman, Ghost &l){
    std::pair<int, int> p = {pacman.getPosition().x/width_ratio, pacman.getPosition().y/height_ratio};
    if (pacman.getTarget().where == -1)
        return pacman.get_position();
    p.first += 4*pacman.getTarget().d * (pacman.getTarget().where == 0);
    p.second += 4*pacman.getTarget().d * (pacman.getTarget().where == 1);
    while (is_possible(p) && pacman_map[p.second][p.first] == 1){
        p.first -= pacman.getTarget().d * (pacman.getTarget().where == 0);
        p.second -= pacman.getTarget().d * (pacman.getTarget().where == 1);
    }
    return p;
}

std::pair<int, int> inky_target(MovingObject &pacman, Ghost &blinky){
    std::pair<int, int> p = {pacman.getPosition().x/width_ratio, pacman.getPosition().y/height_ratio};
    p.first = 2*p.first - blinky.getPosition().x/width_ratio;
    p.second = 2*p.second - blinky.getPosition().y/height_ratio;

    if (p.second >= MAP_WIDTH || p.first >= MAP_HEIGHT) return std::make_pair(blinky.getPosition().x/width_ratio, blinky.getPosition().y/height_ratio);
    if (pacman_map[p.second][p.first] == 1)
       return nearest_move(p);
    return p;
}
std::pair<int, int> clyde_target(MovingObject &pacman, Ghost &clyde){
    std::pair<int, int> p = {pacman.getPosition().x/width_ratio, pacman.getPosition().y/height_ratio};
    if (distance(p.first, p.second, clyde.getPosition().x/width_ratio, clyde.getPosition().y/height_ratio) < 5){
        return std::make_pair(0, 0);
    }else{
        return p;
    }
}

