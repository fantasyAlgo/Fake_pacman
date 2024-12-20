#pragma once

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <utility>
#include "helpers.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "GameStates.h"
#include "make_entities.h"

struct Button {
  std::string name;
  sf::Text text;
  GameState actionWhenPressed;
};

class GUI {
  private:
    sf::Font font;
    // For the Home screen
    sf::Text game_name;

    sf::Texture pacman_img;
    sf::Sprite pacman_ui;

    sf::Texture maze_img;
    sf::Sprite maze_ui;

    std::vector<Button> buttons;
    Button undo_button;
    int size;

    // For the Death screen
    sf::Text death_text;
    sf::Text options_text;
    
    std::vector<std::string> mazes_names;
    std::vector<sf::Text> mazes_texts;

    int pointer_pos;
    void make_text(sf::Text &text, std::string txt, int size, int height, sf::Color);
    void ClearPointers();
  public:
    bool isEnterPressed;
    GUI();
    void goUp(GameState state);
    void goDown();

    GameState DrawHomeScreen(sf::RenderWindow &window);
    GameState DrawOptionsScreen(sf::RenderWindow &window, std::string &current_maze);
};
