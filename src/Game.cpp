#include "Game.hpp"
#include <SFML/System/Time.hpp>

Game::Game(){
  this->isAlive = true;

  this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "FakePacman");
  this->sizeDivisor = 30.0;
  float pac_mov_time = 0;
  load_textures();

  this->pacman = new MovingObject(width_ratio/sizeDivisor, VELOCITY, std::make_pair(17, 19));
  this->blinky = new Ghost(width_ratio/sizeDivisor, VELOCITY, std::make_pair(14, 14), blinky_mov,[](MovingObject &pacman, Ghost &p2){return pacman.get_position();}, std::make_pair(1, 1));
  this->inky = new Ghost(width_ratio/sizeDivisor, VELOCITY, std::make_pair(13, 14), inky_mov, inky_target, std::make_pair(MAP_WIDTH-2, MAP_HEIGHT-2));
  this->clyde = new Ghost(width_ratio/sizeDivisor, VELOCITY, std::make_pair(14, 13), clyde_mov, clyde_target, std::make_pair(MAP_HEIGHT-1, 1));
  this->pinky = new Ghost(width_ratio/sizeDivisor, VELOCITY, std::make_pair(14, 15), pinky_mov, pinky_target, std::make_pair(1, MAP_HEIGHT-2));

  this->font.loadFromFile("assets/arial.ttf");
  this->points.setFont(font);
  this->points.setCharacterSize(24);
  this->points.setFillColor(sf::Color::White);
  this->points.setPosition(5, 5);

  this->map = build_map();
  this->coins = make_coins();
  this->powers = make_power();

  srand(0);
  int p_x = 15;
  int p_y = 11;
  this->pac_mov_time = 0;

  this->time = 0;
  this->init_coins = coins.size();
  this->eat_points = 0;
}

void Game::Run(){
  sf::Clock clock;
  sf::Time time;
  while (this->isOpen()){
    time = clock.restart()*7000.0f;
    std::cout << "time: " << time.asSeconds() << std::endl;
    this->KeyHandler();
    this->Update(time);
    this->Render();
  }
}
void Game::KeyHandler(){
  sf::Event event;
  while (window->pollEvent(event)){

    if (event.type == sf::Event::Closed)
        window->close();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        new_target.d = 1;
        new_target.where = 1;
        new_target.is_finished = false;
        new_target.init = false;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        new_target.d = -1;
        new_target.where = 1;
        new_target.is_finished = false;
        new_target.init = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        new_target.d = 1;
        new_target.where = 0;
        new_target.is_finished = false;
        new_target.init = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        new_target.d = -1;
        new_target.where = 0;
        new_target.is_finished = false;
        new_target.init = false;
    }
  }
}


void Game::Update(sf::Time deltaTime){
  pacman->setTexture(pac_mov[int(pac_mov_time)%3]);
  if (pacman->getTarget().where == 1) pacman->setRotation(-pacman->getTarget().d*90);
  else if (pacman->getTarget().where == 0) pacman->setRotation(pacman->getTarget().d == 1 ? 180 : 0);

  pac_mov_time += 0.001;
  pacman->update(new_target, deltaTime);
  blinky->updateGhost(*pacman, *blinky, time > 0, eat_points, deltaTime);
  pinky->updateGhost(*pacman, *pinky, time > 0, eat_points, deltaTime);
  inky->updateGhost(*pacman, *blinky, time > 0, eat_points, deltaTime);
  clyde->updateGhost(*pacman, *clyde, time > 0, eat_points, deltaTime);


  // check if pacman is the same position as one of ghosts
  if (blinky->can_kill(*pacman, time > 0) || pinky->can_kill(*pacman, time > 0) || inky->can_kill(*pacman, time > 0) || clyde->can_kill(*pacman, time > 0)){
    this->isAlive = false;
    return;
  }
  points.setString("Points: " + std::to_string(init_coins - coins.size() + eat_points));
  time -= 0.00003;
}

void Game::Render(){
  window->clear();

  window->draw(*pacman);
  window->draw(*pinky);
  window->draw(*inky);
  window->draw(*clyde);
  window->draw(*blinky);

  for (int i = 0; i < map.size(); i++)
      window->draw(map[i]);
  for (int i = 0; i < coins.size(); i++){
    if (int(pacman->getPosition().x/width_ratio) == coins[i].get_index().first && int(pacman->getPosition().y/height_ratio) == coins[i].get_index().second){
        coins.erase(coins.begin() + i);
        i--;
    }
    if (i >= 0) window->draw(coins[i]);
  }
  for (int i = 0; i < powers.size(); i++){
    if (int(pacman->getPosition().x/width_ratio) == powers[i].get_index().first && int(pacman->getPosition().y/height_ratio) == powers[i].get_index().second){
        powers.erase(powers.begin() + i);
        i--;
        time = 1;
        blinky->setDied(false);
        pinky->setDied(false);
        inky->setDied(false);
        clyde->setDied(false);
    }
    if (i >= 0) window->draw(powers[i]);
  }
  window->draw(points);
  window->display();
}

bool Game::isOpen(){
  return this->isAlive;
}
Game::~Game(){

}

