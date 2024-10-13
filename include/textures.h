#ifndef Textures_H
#define Textures_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

extern sf::Texture pac_mov[3];
extern sf::Texture inky_mov[2];
extern sf::Texture pinky_mov[2];
extern sf::Texture clyde_mov[2];
extern sf::Texture blinky_mov[2];
extern sf::Texture scared_ghost[2];
extern sf::Texture pacman_death[10];
extern sf::Texture atlasTexture;

void load_textures();

#endif // !Textures_H
