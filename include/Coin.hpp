#ifndef Coin_H 
#define Coin_H 

#include <SFML/Graphics.hpp>
#include <utility>

class Coin : public sf::CircleShape{
  private:
  std::pair<int, int> index;
  public:
    Coin(float radius, std::pair<int, int> index);
    std::pair<int, int> get_index();
};

#endif
