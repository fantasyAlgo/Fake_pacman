sf::Texture make_texture(string path){
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

class MovingObject : public sf::Sprite {
    protected:
        Target target;
        pair<int, int> p;
        float vel;
    public:
        MovingObject(float radius, float vel, pair<int, int> position, sf::Texture texture2) : sf::Sprite(texture2){
            //this->setFillColor(color);
            this->p = position;
            this->vel = vel;
            setPosition(p.first*width_ratio + width_ratio/POS_DIV, p.second*height_ratio + height_ratio/POS_DIV);
            setScale(radius, radius);
            //setOrigin(position.first, position.second);
            setOrigin(width_ratio/POS_DIV, height_ratio/POS_DIV);
            setTexture(texture2);
        }
        void set_target(Target target){ this->target = target;}
        void set_position(pair<int, int> p){
            this->p = p;
            setPosition(p.first*width_ratio + width_ratio/POS_DIV, p.second*height_ratio + height_ratio/POS_DIV);
        }
        void set_velocity(float vel){this->vel = vel;}
        float get_velocity(){return vel;}
        Target getTarget(){return target;}
        pair<int, int> get_position(){return p;}
        pair<int, int> get_map_coord(){return make_pair(getPosition().x/width_ratio, getPosition().y/height_ratio);}
        Target get_target(){return target;}

        void update(Target new_target){
            if (target.is_finished)
                target = new_target;
                
            if (!target.init && !target.is_finished && can_go(p.second + target.d * (target.where == 1), p.first + target.d * (target.where == 0))
                && pacman_map[p.second + target.d * (target.where == 1)][p.first + target.d * (target.where == 0)] != 1){
                p.first += target.d * (target.where == 0);
                p.second += target.d * (target.where == 1);
                target.init = true;
            }else if (!target.init && !target.is_finished){
                target.is_finished = true;
                target.init = true;
            }
            if (!target.is_finished)
                move(target.d * (target.where == 0) * vel * width_ratio, target.d * (target.where == 1) * vel * height_ratio);

            if (in_interval(getPosition().x, p.first*width_ratio+width_ratio/POS_DIV, 1) && in_interval(getPosition().y, p.second*height_ratio+height_ratio/POS_DIV, 1)){
                target.is_finished = true;
                target.init = true;
            }
        }
        Target go_to(pair<int, int> target_position){
            pair<int, int> p_p = make_pair(getPosition().x/width_ratio, getPosition().y/height_ratio);
            //cout << "pog: " << p.first << ", " << p.second << endl;
            pair<int, int> best_dir = BFS(pacman_map, p_p, target_position);
            //cout << best_dir.first << ", " << best_dir.second << ", pos: " << target_position.first << endl;
            Target target;
            target.where = best_dir.first - this->p.first == 0 ? 1 : 0;
            target.d = target.where == 1 ? best_dir.second - this->p.second : best_dir.first - this->p.first;
            target.is_finished = false;
            target.init = false;
            return target;
        }

};

class Ghost : public MovingObject {
    public:
        Ghost(float radius, float vel, pair<int, int> position, sf::Texture texture2, sf::Texture ghost_mov[2], void(*action)(MovingObject p1, MovingObject p2)) : MovingObject(radius, vel, position, texture2){
            sf::Texture move_texture = ghost_mov;
            setTexture(move_text);
            auto action = action;
            float time = 0;
        }
        updateGhost(MovingObject pacman, MovingObject guest){
            go_to(action(pacman, guest));
            setTexture(move_texture[int(time+0.01)%2]);
            time += 0.001;
        }
};