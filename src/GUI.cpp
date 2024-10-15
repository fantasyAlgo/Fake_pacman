#include "GUI.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <algorithm>
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
  for (int i = 0; i < this->size; i++) {
    this->buttons[i].text.setString(this->buttons[i].name);
  }
}
GUI::GUI(){
  if (!font.loadFromFile("assets/Emulogic.ttf"))
    throw std::runtime_error("Wasn't able to find the font");
  this->mazes_names = loadMapNames("mazes/mazeList.txt");
  int size = this->mazes_names.size();
  for (int i = 0; i < size; i++) {
    sf::Text text;
    this->make_text(text, this->mazes_names[i], 30, SCREEN_WIDTH/2 + (i+1)*(SCREEN_WIDTH/8), sf::Color::White);
    this->mazes_texts.push_back(text);
  }

  this->buttons.push_back({"New game", sf::Text(), GameState::PrepareRun});
  this->buttons.push_back({"Options", sf::Text(), GameState::Options});
  this->buttons.push_back({"Exit", sf::Text(), GameState::KillProgram});
  this->size = this->buttons.size();

  int y = 100;
  this->make_text(this->game_name, "Pacman", 100, y, sf::Color(237, 231, 109));
  this->make_text(this->options_text, "Select map", 70, y, sf::Color(237, 231, 109));

  y += SCREEN_WIDTH/2;
  this->undo_button = {"Undo", sf::Text(), GameState::Home};
  this->make_text(this->undo_button.text, "Undo", 50, SCREEN_WIDTH/3 + (SCREEN_WIDTH/8)*NVisibleMazes, sf::Color::White);
  for (int i = 0; i < this->size; i++) {
    this->make_text(buttons[i].text, buttons[i].name, 40, y, sf::Color::White);
    y += SCREEN_WIDTH/8;
  }

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
  for (int i = 0; i < this->size; i++) 
    if (this->pointer_pos == i) buttons[i].text.setString(">"+buttons[i].name);

  //window.draw(this->maze_ui);
  window.draw(this->game_name);
  for (int i = 0; i < size; i++)
    window.draw(this->buttons[i].text);

  if (this->isEnterPressed){
    this->isEnterPressed = false;
    for (int i = 0; i < this->size; i++) {
      if (this->pointer_pos == i){
        return this->buttons[i].actionWhenPressed;
      }
    }
  }
  window.draw(this->pacman_ui);

  window.display();
  return GameState::Home;
}
GameState GUI::DrawOptionsScreen(sf::RenderWindow &window, std::string &current_maze){
  window.clear(sf::Color(47, 49, 158));
  window.draw(this->options_text);
  int size = mazes_texts.size();
  for (int i = 0; i < size; i++) {
    if (this->pointer_pos ==  i)
      this->mazes_texts[i].setString(">" + this->mazes_names[i]);
    else this->mazes_texts[i].setString(this->mazes_names[i]);
    this->mazes_texts[i].setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT+100);
  }
  if (this->pointer_pos == size)
    undo_button.text.setString(">" + undo_button.name);
  else undo_button.text.setString(undo_button.name);
  int pos = this->pointer_pos;
  if (pos-1 >= 0) this->mazes_texts[pos-1].setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/3);
  if (pos >= 0 && pos < size) this->mazes_texts[pos].setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/3 + 1*(SCREEN_HEIGHT/8));
  if (pos+1 < size) this->mazes_texts[pos+1].setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/3 + 2*(SCREEN_HEIGHT/8));

  for (int i = 0; i < size; i++) 
    window.draw(this->mazes_texts[i]);
  window.draw(undo_button.text);

  if (this->isEnterPressed){
    this->isEnterPressed = false;
    for (int i = 0; i < size; i++) 
      if (this->pointer_pos == i){
        std::cout << "Loading: " << this->mazes_names[i] << std::endl;
        current_maze = this->mazes_names[i];
      }
    if (this->pointer_pos == size) return undo_button.actionWhenPressed;
  }

  window.display();
  return GameState::Options;
}


void GUI::goUp(GameState state){
  this->pointer_pos += 1;
  this->pointer_pos = std::min(this->pointer_pos, state == GameState::Home ? 2 : (int)this->mazes_texts.size());
}
void GUI::goDown(){
  this->pointer_pos -= 1;
  this->pointer_pos = std::max(this->pointer_pos, 0);
}
