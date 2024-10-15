#include "Settings.h"
#include <cstdio>
#include <fstream>
#include <stdexcept>

int pacman_map[MAP_HEIGHT][MAP_WIDTH];


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
    //std::cout << line << std:
    for (int j = 0;  j < MAP_WIDTH; j++) {
      if (j < line.size())
        pacman_map[i][j] = (int)line.at(j)-48;
    }
    i++;
  }
  file.close();
}

