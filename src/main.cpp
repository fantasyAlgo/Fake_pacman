#include "Game.hpp"

int main () {
  Game game;
  while (game.isOpen())
    game.update();
  return 0;
}
