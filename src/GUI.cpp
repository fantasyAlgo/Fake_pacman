#include "GUI.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <stdexcept>


void GUI::make_text(sf::Text &text, std::string txt, int size, int height, sf::Color color){
  text.setString(txt);
  text.setFont(font);
  text.setCharacterSize(size);

  sf::FloatRect textBounds = text.getLocalBounds();
  text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                 textBounds.top + textBounds.height / 2.0f);

  text.setPosition(SCREEN_WIDTH/2, height);

  text.setFillColor(color);
}
void GUI::ClearPointers(){
  this->new_game.text.setString(this->new_game.name);
  this->exit_game.text.setString(this->exit_game.name);
}
GUI::GUI(){
  if (!font.loadFromFile("assets/Emulogic.ttf"))
    throw std::runtime_error("Wasn't able to find the font");
  int y = 100;
  this->make_text(this->game_name, "Pacman", 100, y, sf::Color(237, 231, 109));
  y += SCREEN_WIDTH/2;

  sf::Text new_game_text;
  this->make_text(new_game_text, "New game", 30, y, sf::Color::White);
  this->new_game = (Button){"New game", new_game_text, GameState::PrepareRun};

  y += SCREEN_WIDTH/8;
  sf::Text exit_game_text;
  this->make_text(exit_game_text, "Exit ", 30, y, sf::Color::White);
  this->exit_game = {"Exit", exit_game_text, GameState::KillProgram};

  if (!this->pacman_img.loadFromFile("assets/images/pacmanImg.png")){ throw std::runtime_error("Whoops!");}
  this->pacman_ui.setPosition(SCREEN_WIDTH/2 - 60, 200);
  this->pacman_ui.setScale(0.12f, 0.12f);
  this->pacman_ui.setTexture(this->pacman_img);

  if (!this->maze_img.loadFromFile("assets/images/maze.png")){ throw std::runtime_error("Whoops!");}
  this->maze_ui.setPosition(0, 0);
  this->maze_ui.setTexture(this->maze_img);
  this->maze_ui.setScale(3.6f, 3.15f);

  this->pointer_pos = 0;
  this->isEnterPressed = false;
}
GameState GUI::DrawHomeScreen(sf::RenderWindow &window){
  window.clear(sf::Color(47, 49, 158));
  this->ClearPointers();
  if (this->pointer_pos == 0) this->exit_game.text.setString("> " + this->exit_game.name);
  else this->new_game.text.setString("> " + this->new_game.name);

  window.draw(this->maze_ui);
  window.draw(this->game_name);
  window.draw(this->new_game.text);
  window.draw(this->exit_game.text);

  if (this->isEnterPressed){
    this->isEnterPressed = false;
    if (this->pointer_pos == 0) return this->exit_game.actionWhenPressed;
    else return this->new_game.actionWhenPressed;
  }
  window.draw(this->pacman_ui);

  window.display();
  return GameState::Home;
}
GameState GUI::DrawDeathScreen(sf::RenderWindow &window){
  return GameState::Home;
}


void GUI::goUp(GameState state){
  this->pointer_pos += 1;
  this->pointer_pos = std::min(this->pointer_pos, 1);
}
void GUI::goDown(){
  this->pointer_pos -= 1;
  this->pointer_pos = std::max(this->pointer_pos, 0);
}
