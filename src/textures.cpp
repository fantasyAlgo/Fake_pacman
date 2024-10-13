#include "textures.h"
#include <stdexcept>


sf::Texture pac_mov[3];
sf::Texture inky_mov[2];
sf::Texture pinky_mov[2];
sf::Texture clyde_mov[2];
sf::Texture blinky_mov[2];
sf::Texture scared_ghost[2];
sf::Texture pacman_death[10];
sf::Texture atlasTexture;

void load_textures(){
  pac_mov[0].loadFromFile("assets/pacman/0.png");
  pac_mov[1].loadFromFile("assets/pacman/1.png");
  pac_mov[2].loadFromFile("assets/pacman/2.png");

  inky_mov[0].loadFromFile("assets/ghosts/y-0.png");
  inky_mov[1].loadFromFile("assets/ghosts/y-1.png");

  pinky_mov[0].loadFromFile("assets/ghosts/p-0.png");
  pinky_mov[1].loadFromFile("assets/ghosts/p-1.png");

  clyde_mov[0].loadFromFile("assets/ghosts/b-0.png");
  clyde_mov[1].loadFromFile("assets/ghosts/b-1.png");

  blinky_mov[0].loadFromFile("assets/ghosts/r-0.png");
  blinky_mov[1].loadFromFile("assets/ghosts/r-1.png");

  scared_ghost[0].loadFromFile("assets/ghosts/f-0.png");
  scared_ghost[1].loadFromFile("assets/ghosts/f-1.png");

  if (!atlasTexture.loadFromFile("assets/images/atlasMap.png")) throw std::runtime_error("There is a problem with your file!");

  std::string filePath;
  for (int i = 1; i <= 10; i++) {
    filePath = (std::string)"assets/pacman/d-" + std::to_string(i) + (std::string)".png";
    if (!pacman_death[i-1].loadFromFile(filePath))
      throw std::runtime_error("asset image is corrupted or does not exist");
  }
}


