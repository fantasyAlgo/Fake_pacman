#include "Ghost.hpp"

Ghost::Ghost(float radius, float vel, std::pair<int, int> position, sf::Texture ghost_mov[2], std::pair<int, int>(*actionF)(MovingObject &p1, Ghost &p2), std::pair<int, int> scatter_place) : MovingObject(radius, vel, position){
    move_texture[0] = ghost_mov[0];
    move_texture[1] = ghost_mov[1];
    action = actionF;
    time = 0;
    died_time = 0;
    died = false;
    this->scatter_place = scatter_place;
}
void Ghost::setDied(bool died){this->died = died;}
std::pair<int, int> Ghost::random_target(){
    std::pair<int, int> p = {getPosition().x/width_ratio, getPosition().y/height_ratio};
    p.first = p.first + (rand()%3)-1;
    p.second = p.second + (rand()%3)-1;
    if (pacman_map[p.second][p.first] == 1)
        return nearest_move(p);
    return p;
}
bool Ghost::can_kill(MovingObject &pacman, bool scared){
    if (died) scared = false;
    return get_map_coord() == pacman.get_map_coord() && !scared;
}
void Ghost::updateGhost(MovingObject &pacman, Ghost &guest, bool scared, int &eat_points){
    if (died_time > 0){
        died_time -= 0.0001;
        return;
    }
    if (scared == false) died = false;
    if (died) scared = false;
    if (int(time)%100 > 60 && int(time)%1000 < 85 && !scared) update(go_to(scatter_place));
    else update(go_to(!scared ? action(pacman, guest) : random_target()));
    setTexture(!scared ? move_texture[int(time+0.01)%2] : scared_ghost[int(time+0.01)%2]);
    // Check if pacman has collided to the ghost
    if (get_map_coord() == pacman.get_map_coord() && scared){
        set_position(std::make_pair(14, 14));
        died_time = 1;
        died = true;
        eat_points += 10;
    }
    time += 0.001;
}

