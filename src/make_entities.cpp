#include "make_entities.h"


std::vector<std::string> loadMapNames(std::string mazesNameTxt){
  std::ifstream file(mazesNameTxt);
  std::vector<std::string>  result;
  std::string line;
  while (getline(file, line))
    result.push_back(line);
  file.close();
  return result;
}

void loadMap(std::string mapFile){
  std::ifstream file(mapFile);
  std::string line;
  int i = 0;
  while (getline(file, line)){
    for (int j = 0;  j < MAP_WIDTH; j++) {
      if (j < line.size())
        pacman_map[i][j] = (int)line.at(j)-48;
    }
    i++;
  }
  file.close();
}


sf::Texture build_map(sf::Texture &atlasTexture){
  std::vector<sf::RectangleShape> map;


  sf::RenderTexture renderTexture;
  if (!renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT)) throw std::runtime_error("renderTexture is not working!");
  sf::Sprite sprite;
  sprite.setTexture(atlasTexture);
  renderTexture.clear();

  // little optimization
  int width;
  std::cout << width_ratio << std::endl;

  sf::IntRect tileRect;
  // Does not work cat!!!!!!!!
  for (int i = 0; i < MAP_HEIGHT; i++){

    width = width_ratio;
    for (int j = 0; j < MAP_WIDTH; j++){
      if (pacman_map[i][j] != 1) continue;
      tileRect = sf::IntRect(0, 0, 16, 16);
      if ( (j-1 >= 0 && pacman_map[i][j-1] == 1) && (j+1 < MAP_WIDTH && pacman_map[i][j+1] == 1)) tileRect = sf::IntRect(16*6,0, 16, 16);
      if ( (i-1 >= 0 && pacman_map[i-1][j] == 1) && (i+1 < MAP_HEIGHT && pacman_map[i+1][j] == 1)) tileRect = sf::IntRect(16*9,0, 16, 16);

      if ((j-1 >= 0 && pacman_map[i][j-1] != 1) && (j+1 < MAP_WIDTH && pacman_map[i][j+1] == 1) &&
          (i-1 >= 0 && pacman_map[i-1][j] != 1) && (i+1 < MAP_HEIGHT && pacman_map[i+1][j] != 1)) tileRect = sf::IntRect(16*4,0, 16, 16);

      if ((j-1 >= 0 && pacman_map[i][j-1] == 1) && (j+1 < MAP_WIDTH && pacman_map[i][j+1] != 1) &&
          (i-1 >= 0 && pacman_map[i-1][j] != 1) && (i+1 < MAP_HEIGHT && pacman_map[i+1][j] != 1)) tileRect = sf::IntRect(16*2,0, 16, 16);

      if ((j-1 >= 0 && pacman_map[i][j-1] == 1) && (j+1 >= MAP_WIDTH || pacman_map[i][j+1] != 1) &&
          (i-1 < 0 || pacman_map[i-1][j] != 1) && (i+1 < MAP_HEIGHT && pacman_map[i+1][j] == 1)) tileRect = sf::IntRect(16*3,0, 16, 16);

      if ((j-1 < 0 || pacman_map[i][j-1] != 1) && (j+1 >= MAP_WIDTH || pacman_map[i][j+1] == 1) &&
          (i-1 < 0 || pacman_map[i-1][j] != 1) && (i+1 >= MAP_HEIGHT || pacman_map[i+1][j] == 1)) tileRect = sf::IntRect(16*5,0, 16, 16);

      if ((j-1 < 0 || pacman_map[i][j-1] != 1) && (j+1 >= MAP_WIDTH || pacman_map[i][j+1] == 1) &&
          (i-1 < 0 || pacman_map[i-1][j] == 1) && (i+1 >= MAP_HEIGHT || pacman_map[i+1][j] != 1)) tileRect = sf::IntRect(16*12,0, 16, 16);

      if ((j-1 < 0 || pacman_map[i][j-1] == 1) && (j+1 >= MAP_WIDTH || pacman_map[i][j+1] != 1) &&
          (i-1 < 0 || pacman_map[i-1][j] == 1) && (i+1 >= MAP_HEIGHT || pacman_map[i+1][j] != 1)) tileRect = sf::IntRect(16*10,0, 16, 16);


      sprite.setTextureRect(tileRect);
      sprite.setScale(2.0f, 2.0f);
      sprite.setPosition((j+1)*width_ratio - width, i*height_ratio);
      renderTexture.draw(sprite);

    }
  }
  renderTexture.display();
  return renderTexture.getTexture();
}
std::vector<Coin> make_coins(){
  std::vector<Coin> coins;
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (pacman_map[i][j] == 0){
                Coin coin(width_ratio/6, std::make_pair(j, i));
                coin.setFillColor(sf::Color::Yellow);
                coin.setPosition(j*width_ratio + width_ratio/2, i*height_ratio + height_ratio/2);
                coins.push_back(coin);
            }
        }
    }
    return coins;
}

std::vector<POWER_UP> make_power(){
  std::vector<POWER_UP> power;
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (pacman_map[i][j] == 2){
                POWER_UP coin(width_ratio/4, std::make_pair(j, i));
                coin.setFillColor(sf::Color::Yellow);
                coin.setPosition(j*width_ratio + width_ratio/2, i*height_ratio + height_ratio/2);
                power.push_back(coin);
            }
        }
    }
    return power;
}
