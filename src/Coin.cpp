#include "Coin.hpp"

Coin::Coin(float radius, std::pair<int, int> index){
  this->setRadius(radius);
  this->index = index;
  this->setFillColor(sf::Color::Yellow);
}
std::pair<int, int> Coin::get_index(){
    return index;
}


