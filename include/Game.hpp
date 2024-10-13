#ifndef Game_H
#define Game_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <iostream>
#include <time.h>

#include "Settings.h"
#include "Ghost.hpp"
#include "MovingObject.hpp"
#include "Coin.hpp"

#include "make_entities.h"

#include "ghost_mov.hpp"
#include "GameStates.h"
#include "GUI.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <SFML/Audio.hpp>

class Game{
public:
  Game();
  void KeyHandler();
  void Reset();
  GameState Update(sf::Time deltaTime);
  void Render();
  void Run();
  bool isOpen();
  ~Game();
private:
  bool isAlive;
  GameState state;
  GUI gui;

  sf::RenderWindow *window;
  MovingObject *pacman;
  Ghost *blinky;
  Ghost *inky;
  Ghost *clyde;
  Ghost *pinky;
  sf::Font font;
  sf::Text points;

  //std::vector<sf::RectangleShape> map;
  sf::Sprite mapSprite;
  sf::Texture mapTexture;
  std::vector<Coin> coins;
  std::vector<POWER_UP> powers;
  Target new_target;

  // For the music
  sf::Music beginMusic;
  sf::Music deathMusic;
  sf::SoundBuffer pacman_chomp_buf;
  sf::Sound pacman_chomp;
  sf::SoundBuffer ghost_death_buf;
  sf::Sound ghost_death;

  float sizeDivisor;
  float time;
  int init_coins;
  int eat_points;
  float pac_mov_time;
  float peace_time;

  float death_time;
  bool death_animation;
  int death_frame;
};

#endif
