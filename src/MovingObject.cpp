#include "MovingObject.hpp"



MovingObject::MovingObject(float radius, float vel, std::pair<int, int> position) : sf::Sprite(){
    //this->setFillColor(color);
    this->p = position;
    this->vel = vel;
    setPosition(p.first*width_ratio + width_ratio/POS_DIV, p.second*height_ratio + height_ratio/POS_DIV);
    setScale(radius, radius);
    //setOrigin(position.first, position.second);
    setOrigin(width_ratio/POS_DIV, height_ratio/POS_DIV);
    //setTexture(texture2);
}
void MovingObject::set_target(Target target){ this->target = target;}
void MovingObject::set_position(std::pair<int, int> p){
    this->p = p;
    setPosition(p.first*width_ratio + width_ratio/POS_DIV, p.second*height_ratio + height_ratio/POS_DIV);
}
void MovingObject::set_velocity(float vel){this->vel = vel;}
float MovingObject::get_velocity(){return vel;}
Target MovingObject::getTarget(){return target;}
std::pair<int, int> MovingObject::get_position(){return p;}
std::pair<int, int> MovingObject::get_map_coord(){return std::make_pair(getPosition().x/width_ratio, getPosition().y/height_ratio);}
Target MovingObject::get_target(){return target;}

void MovingObject::update(Target new_target, sf::Time deltaTime){
  if (target.is_finished)
      target = new_target;

  //std::cout << target.d << " | " << target.where << " .... " << p.first << p.second <<std::endl;
  float DT = deltaTime.asSeconds();
  float nPosX = p.first + target.d * (target.where == 0);
  float nPosY = p.second + target.d * (target.where == 1);
     
  if (!target.init && !target.is_finished && can_go(nPosY, nPosX) && pacman_map[(int)nPosY][(int)nPosX] != 1){
      p.first = nPosX;
      p.second = nPosY;
      target.init = true;
  }else if (!target.init && !target.is_finished){
      target.is_finished = true;
      target.init = true;
  }
  if (!target.is_finished)
      move(target.d * (target.where == 0) * vel * width_ratio * DT, target.d * (target.where == 1) * vel * height_ratio * DT);

  if (in_interval(getPosition().x, p.first*width_ratio+width_ratio/POS_DIV, 1) && in_interval(getPosition().y, p.second*height_ratio+height_ratio/POS_DIV, 1)){
      target.is_finished = true;
      target.init = true;
  }
}
Target MovingObject::go_to(std::pair<int, int> target_position){
    std::pair<int, int> p_p = std::make_pair(getPosition().x/width_ratio, getPosition().y/height_ratio);
    std::pair<int, int> best_dir = BFS(pacman_map, p_p, target_position);
    Target target;
    target.where = best_dir.first - this->p.first == 0 ? 1 : 0;
    target.d = target.where == 1 ? best_dir.second - this->p.second : best_dir.first - this->p.first;
    target.is_finished = false;
    target.init = false;
    return target;
}

