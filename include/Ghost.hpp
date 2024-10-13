#ifndef Ghost_H 
#define Ghost_H 

#include <SFML/Graphics.hpp>

#include "MovingObject.hpp"
#include "Settings.h"
#include "textures.h"
#include "pathFinding.h"
#include <utility>

class Ghost : public MovingObject {
  private:
      sf::Texture move_texture[2];
  std::pair<int, int>(*action)(MovingObject &p1, Ghost &p2);
      float time;
      float died_time;
      bool died;
  std::pair<int, int> scatter_place;
  public:
  Ghost(float radius, float vel, std::pair<int, int> position, sf::Texture ghost_mov[2], std::pair<int, int>(*actionF)(MovingObject &p1, Ghost &p2), 
        std::pair<int, int> scatter_place);
  std::pair<int, int> random_target();
    void setDied(bool died);
    bool can_kill(MovingObject &pacman, bool scared);

    // This function returns if the ghost has been eaten or not
    bool updateGhost(MovingObject &pacman, Ghost &guest, bool scared, int &eat_points, sf::Time deltaTime);
};

#endif
