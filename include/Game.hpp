#ifndef Game_H
#define Game_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <time.h>

#include "Settings.h"
#include "Ghost.hpp"
#include "MovingObject.hpp"
#include "Coin.hpp"
#include "make_entities.h"
#include "ghost_mov.hpp"


class Game{
public:
  Game();
  void update();
  bool isOpen();
  ~Game();
private:
  bool isAlive;

  sf::RenderWindow *window;
  MovingObject *pacman;
  Ghost *blinky;
  Ghost *inky;
  Ghost *clyde;
  Ghost *pinky;
  sf::Font font;
  sf::Text points;

  std::vector<sf::RectangleShape> map;
  std::vector<Coin> coins;
  std::vector<POWER_UP> powers;
  Target new_target;

  float sizeDivisor;
  float time;
  int init_coins;
  int eat_points;
  float pac_mov_time;
};

#endif
