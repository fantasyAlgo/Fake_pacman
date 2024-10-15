#include "Game.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>

Game::Game(){
  loadMap("mazes/maze1.map");
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

  this->font.loadFromFile("assets/Emulogic.ttf");
  this->points.setFont(font);
  this->points.setCharacterSize(24);
  this->points.setFillColor(sf::Color::White);
  this->points.setPosition(5, 5);

  this->mapTexture = build_map(atlasTexture);
  this->mapSprite.setTexture(this->mapTexture);

  this->coins = make_coins();
  this->powers = make_power();

  // Music
  if (!this->beginMusic.openFromFile("assets/music/pacman_beginning.wav")) throw std::runtime_error("Begin music bad!");
  if (!this->deathMusic.openFromFile("assets/music/pacman_death.wav")) throw std::runtime_error("Death music bad bad!");
  if (!this->pacman_chomp_buf.loadFromFile("assets/music/pacman_chomp.wav")) throw std::runtime_error("Chomp bad!");
  if (!this->ghost_death_buf.loadFromFile("assets/music/pacman_eatghost.wav")) throw std::runtime_error("Ghost death bad!");
  this->beginMusic.setVolume(30.0f);
  this->deathMusic.setVolume(30.0f);
  this->pacman_chomp.setBuffer(this->pacman_chomp_buf);
  this->ghost_death.setBuffer(this->ghost_death_buf);

  srand(0);
  this->pac_mov_time = 0;

  this->time = 0;
  this->init_coins = coins.size();
  this->eat_points = 0;

  this->state = GameState::Home;
  this->current_maze = "maze1.map";
}

void Game::Reset(){
  loadMap(filePrefix+current_maze);
  this->mapTexture = build_map(atlasTexture);
  this->mapSprite.setTexture(this->mapTexture);

  this->coins = make_coins();
  this->powers = make_power();

  this->pacman->set_position(std::make_pair(17, 19));
  this->blinky->set_position(std::make_pair(14, 14));
  this->inky->set_position(std::make_pair(13, 14));
  this->clyde->set_position(std::make_pair(14, 13));
  this->pinky->set_position(std::make_pair(14, 15));

  this->eat_points = 0;
  this->init_coins = coins.size();
  this->points.setString("Points: " + std::to_string(this->init_coins - coins.size() + eat_points));
  this->state = GameState::RunGame;
  this->new_target = {0, -1, 0, 0};
  this->beginMusic.play();

  this->peace_time = this->beginMusic.getDuration().asSeconds();
  this->death_animation = false;
  this->time = 0;
}

void Game::Run(){
  sf::Clock clock;
  sf::Time time;
  while (true){
    time = clock.restart()*TIME_SPEED;
    this->KeyHandler();
    switch (this->state) {
     case GameState::KillProgram:
        return;
     case GameState::RunGame:
        this->state = this->Update(time);
        this->Render();
        break;
      case GameState::Home:
        this->state = gui.DrawHomeScreen(*this->window);
        break;
      case GameState::PrepareRun:
        this->Reset();
        this->state = GameState::RunGame;
        break;
      case GameState::Options:
        this->state = gui.DrawOptionsScreen(*this->window, this->current_maze);
        break;

    }
  }
}

void Game::KeyHandler(){
  sf::Event event;
  while (window->pollEvent(event)){

    if (event.type == sf::Event::Closed){
      window->close();
      this->state=  GameState::KillProgram;
    }

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      gui.goDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      gui.goUp(state);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
      gui.isEnterPressed = true;
    }else gui.isEnterPressed = false;
  }
}


GameState Game::Update(sf::Time deltaTime){
  if (this->death_animation){
    float step = (this->death_time)/this->deathMusic.getDuration().asSeconds() ;
    pacman->setTexture(pacman_death[step >= 0 ? 9-(int)(step*9.0f) : 0]);
    this->death_time -= deltaTime.asSeconds()/TIME_SPEED;
    if (this->death_time < 0){
      this->isAlive = false;
      this->death_animation = false;
      return GameState::Home;
    }
    return GameState::RunGame;
  }
  //std::cout << pac[int(pac_mov_time)%3] << std::endl;
  pacman->setTexture(pac_mov[int(pac_mov_time)%3]);
  if (pacman->getTarget().where == 1) pacman->setRotation(-pacman->getTarget().d*90);
  else if (pacman->getTarget().where == 0) pacman->setRotation(pacman->getTarget().d == 1 ? 180 : 0);
  pac_mov_time += 0.001;

  this->peace_time -= deltaTime.asSeconds()/TIME_SPEED;
  if (this->peace_time > 0) return GameState::RunGame;

  pacman->update(new_target, deltaTime);
  if (blinky->updateGhost(*pacman, *blinky, time > 0, eat_points, deltaTime)) ghost_death.play(); 
  if (pinky->updateGhost(*pacman, *pinky, time > 0, eat_points, deltaTime)) ghost_death.play();
  if (inky->updateGhost(*pacman, *blinky, time > 0, eat_points, deltaTime)) ghost_death.play();
  if (clyde->updateGhost(*pacman, *clyde, time > 0, eat_points, deltaTime)) ghost_death.play();


  // check if pacman is the same position as one of ghosts
  if (blinky->can_kill(*pacman, time > 0) || pinky->can_kill(*pacman, time > 0) || inky->can_kill(*pacman, time > 0) || clyde->can_kill(*pacman, time > 0)){
    this->isAlive = false;
    this->deathMusic.play();
    this->death_time = this->deathMusic.getDuration().asSeconds();
    this->death_animation = true;
    this->death_frame = 0;

    gui.isEnterPressed = false;
    return GameState::RunGame;
  }
  points.setString("Points: " + std::to_string(init_coins - coins.size() + eat_points));
  time -= 0.09*(deltaTime.asSeconds()/TIME_SPEED);
  return GameState::RunGame;
}

void Game::Render(){
  window->clear();

  window->draw(this->mapSprite);

  window->draw(*pacman);
  window->draw(*pinky);
  window->draw(*inky);
  window->draw(*clyde);
  window->draw(*blinky);


  // for (int i = 0; i < map.size(); i++)
  //    window->draw(map[i]);
  
  for (int i = 0; i < coins.size(); i++){
    if (int(pacman->getPosition().x/width_ratio) == coins[i].get_index().first && int(pacman->getPosition().y/height_ratio) == coins[i].get_index().second){
      coins.erase(coins.begin() + i);
      i--;
      pacman_chomp.play();
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

