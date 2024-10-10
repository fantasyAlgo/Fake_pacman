#ifndef MovingObject_H 
#define MovingObject_H 

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include <utility>
#include "helpers.h"
#include "pathFinding.h"

class MovingObject : public sf::Sprite {
    protected:
        Target target;
  std::pair<int, int> p;
        float vel;
    public:
        MovingObject(float radius, float vel, std::pair<int, int> position);
        void set_target(Target target);
        void set_position(std::pair<int, int> p);
        void set_velocity(float vel);

        float get_velocity();
        Target getTarget();

  std::pair<int, int> get_position();
  std::pair<int, int> get_map_coord();

        Target get_target();
        void update(Target new_target);
        Target go_to(std::pair<int, int> target_position);

};

#endif
