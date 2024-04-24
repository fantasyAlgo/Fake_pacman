#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include<climits>
#include <queue>
#include <fstream>
#include "helpers/textures.h"
//#include <bits/stdc++.h>

using namespace std;

#define INFTY INT_MAX
#define MAP_WIDTH 28
#define MAP_HEIGHT 27
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define VELOCITY 0.0013
#define POS_DIV 2
const int width_ratio = SCREEN_WIDTH / MAP_WIDTH;
const int height_ratio = SCREEN_HEIGHT / MAP_HEIGHT;

// Sample map, in theory should be done using a maze generator (the prim's one should be good for this)
int pacman_map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,2,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1},
    {1,1,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1},
    {1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1,1},
    {1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
    {1,0,0,0,1,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
    {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
    {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
    {1,0,0,2,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
inline bool can_go(int x, int y){
    return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
}
bool in_interval(int x, int a, int b){
    return x >= a-b && x <= a+b;
}
float distance(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

class Coin : public sf::CircleShape{
    pair<int, int> index;
    public:
        Coin(float radius, pair<int, int> index){
            this->setRadius(radius);
            this->index = index;
            this->setFillColor(sf::Color::Yellow);
        }
        pair<int, int> get_index(){
            return index;
        }
};
struct Target{
    int d = 0;
    // 0 = up/down 1 = right/left
    int where = -1;
    bool is_finished = true;
    bool init = false;
};

#define POWER_UP Coin
#include "helpers/pathFinding.h"
#include "helpers/moving_obj.h"
#include "helpers/make_map.h"
#include "helpers/ghost_mov.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
    float sizeDivisor = 30.0;
    float pac_mov_time = 0;
    load_textures();
    MovingObject pacman(width_ratio/sizeDivisor, VELOCITY, make_pair(17, 19), pac_mov[0]);
    MovingObject blinky(width_ratio/sizeDivisor, VELOCITY/2, make_pair(14, 14), pac_mov[0]);
    MovingObject inky(width_ratio/sizeDivisor, VELOCITY/2, make_pair(13, 14), pac_mov[0]);
    MovingObject clyde(width_ratio/sizeDivisor, VELOCITY/2, make_pair(14, 13), pac_mov[0]);
    MovingObject pinky(width_ratio/sizeDivisor, VELOCITY/2, make_pair(14, 15), pac_mov[0]);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text points;
    points.setFont(font);
    points.setCharacterSize(24);
    points.setFillColor(sf::Color::White);
    points.setPosition(5, 5);

    srand(time(NULL));
    int p_x = 15;
    int p_y = 11;

    vector<sf::RectangleShape> map = build_map();
    vector<Coin> coins = make_coins();
    vector<POWER_UP> powers = make_power();

    Target target;
    Target new_target;

    float time = 0;
    int init_coins = coins.size();
    int eat_points = 0;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                new_target.d = 1;
                new_target.where = 1;
                new_target.is_finished = false;
                new_target.init = false;
            } 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                new_target.d = -1;
                new_target.where = 1;
                new_target.is_finished = false;
                new_target.init = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                new_target.d = 1;
                new_target.where = 0;
                new_target.is_finished = false;
                new_target.init = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                new_target.d = -1;
                new_target.where = 0;
                new_target.is_finished = false;
                new_target.init = false;
            }
        
        }
        pacman.setTexture(pac_mov[int(pac_mov_time)%3]);
        if (pacman.getTarget().where == 1){
            pacman.setRotation(-pacman.getTarget().d*90);
        }else if (pacman.getTarget().where == 0){
            pacman.setRotation(pacman.getTarget().d == 1 ? 180 : 0);
        }
        if (time > 0){
            blinky.setTexture(scared_ghost[int(pac_mov_time+0.01)%2]);
            pinky.setTexture(scared_ghost[int(pac_mov_time+0.006)%2]);
            inky.setTexture(scared_ghost[int(pac_mov_time+0.001)%2]);
            clyde.setTexture(scared_ghost[int(pac_mov_time+0.5)%2]);

            if ((blinky.get_map_coord() == pacman.get_map_coord() || pinky.get_map_coord() == pacman.get_map_coord() || 
                inky.get_map_coord() == pacman.get_map_coord() || clyde.get_map_coord() == pacman.get_map_coord()) ){
                eat_points += 10;
            }

            if (blinky.get_map_coord() == pacman.get_map_coord()) blinky.set_position(make_pair(14, 14));
            else if (pinky.get_map_coord() == pacman.get_map_coord()) pinky.set_position(make_pair(14, 15));
            else if (inky.get_map_coord() == pacman.get_map_coord()) inky.set_position(make_pair(13, 14));
            else if (clyde.get_map_coord() == pacman.get_map_coord()) clyde.set_position(make_pair(14, 13));

        }else{
            blinky.setTexture(blinky_mov[int(pac_mov_time+0.01)%2]);
            pinky.setTexture(pinky_mov[int(pac_mov_time+0.006)%2]);
            inky.setTexture(inky_mov[int(pac_mov_time+0.001)%2]);
            clyde.setTexture(clyde_mov[int(pac_mov_time+0.5)%2]);
        }

        //pacman.rotate(pac_mov_time/10);
        pac_mov_time += 0.001;

        pacman.update(new_target);
        blinky.update(time <= 0 ? blinky.go_to(pacman.get_position()) : blinky.go_to(random_target(blinky)));
        pinky.update(time <= 0 ? pinky.go_to(pinky_target(pacman)) : pinky.go_to(random_target(pinky)));
        inky.update(time <= 0 ? inky.go_to(inky_target(pacman, blinky)) : inky.go_to(random_target(inky)));
        clyde.update(time <= 0 ? clyde.go_to(clyde_target(clyde, pacman)) : clyde.go_to(random_target(clyde)));

        // check if pacman is the same position as one of ghosts
        if ((blinky.get_map_coord() == pacman.get_map_coord() || pinky.get_map_coord() == pacman.get_map_coord() || 
            inky.get_map_coord() == pacman.get_map_coord() || clyde.get_map_coord() == pacman.get_map_coord()) && time < 0){
            break;
        }
        time -= 0.00003;
        window.clear();

        window.draw(pacman);
        window.draw(pinky);
        window.draw(inky);
        window.draw(clyde);
        window.draw(blinky);

        for (int i = 0; i < map.size(); i++)
            window.draw(map[i]);
        for (int i = 0; i < coins.size(); i++){
            if (int(pacman.getPosition().x/width_ratio) == coins[i].get_index().first && int(pacman.getPosition().y/height_ratio) == coins[i].get_index().second){
                coins.erase(coins.begin() + i);
                i--;
            }
            if (i >= 0) window.draw(coins[i]);
        }
        for (int i = 0; i < powers.size(); i++){
            if (int(pacman.getPosition().x/width_ratio) == powers[i].get_index().first && int(pacman.getPosition().y/height_ratio) == powers[i].get_index().second){
                powers.erase(powers.begin() + i);
                i--;
                time = 1;
            }
            if (i >= 0) window.draw(powers[i]);
        }
        cout << coins.size() << endl;
        points.setString("Points: " + to_string(init_coins - coins.size() + eat_points));
        window.draw(points);
        window.display();
    }

    return 0;
}