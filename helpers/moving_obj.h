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
        MovingObject(float radius, float vel, pair<int, int> position) : sf::Sprite(){
            //this->setFillColor(color);
            this->p = position;
            this->vel = vel;
            setPosition(p.first*width_ratio + width_ratio/POS_DIV, p.second*height_ratio + height_ratio/POS_DIV);
            setScale(radius, radius);
            //setOrigin(position.first, position.second);
            setOrigin(width_ratio/POS_DIV, height_ratio/POS_DIV);
            //setTexture(texture2);
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
            pair<int, int> best_dir = BFS(pacman_map, p_p, target_position);
            Target target;
            target.where = best_dir.first - this->p.first == 0 ? 1 : 0;
            target.d = target.where == 1 ? best_dir.second - this->p.second : best_dir.first - this->p.first;
            target.is_finished = false;
            target.init = false;
            return target;
        }

};

class Ghost : public MovingObject {
    private:
        sf::Texture move_texture[2];
        pair<int, int>(*action)(MovingObject &p1, Ghost &p2);
        float time;
        float died_time;
        bool died;
        pair<int, int> scatter_place;
    public:
        Ghost(float radius, float vel, pair<int, int> position, sf::Texture ghost_mov[2], pair<int, int>(*actionF)(MovingObject &p1, Ghost &p2), pair<int, int> scatter_place) : MovingObject(radius, vel, position){
            move_texture[0] = ghost_mov[0];
            move_texture[1] = ghost_mov[1];
            action = actionF;
            time = 0;
            died_time = 0;
            died = false;
            this->scatter_place = scatter_place;
        }
        pair<int, int> random_target(){
            pair<int, int> p = {getPosition().x/width_ratio, getPosition().y/height_ratio};
            p.first = p.first + (rand()%3)-1;
            p.second = p.second + (rand()%3)-1;
            if (pacman_map[p.second][p.first] == 1)
                return nearest_move(p);
            return p;
        }
        void updateGhost(MovingObject &pacman, Ghost &guest, bool scared, int &eat_points){
            if (died_time > 0){
                died_time -= 0.0001;
                return;
            }
            if (scared == false) died = false;
            if (died) scared = false;
            if (int(time)%100 > 60 && int(time)%1000 < 85 && !scared) update(go_to(scatter_place));
            else update(go_to(!scared ? action(pacman, guest) : random_target()));
            setTexture(!scared ? move_texture[int(time+0.01)%2] : scared_ghost[int(time+0.01)%2]);
            // Check if pacman has collided to the ghost
            if (get_map_coord() == pacman.get_map_coord() && scared){
                set_position(make_pair(14, 14));
                died_time = 1;
                died = true;
                eat_points += 10;
            }
            time += 0.001;
        }
};