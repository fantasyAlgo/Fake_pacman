sf::Texture pac_mov[3];
sf::Texture inky_mov[2];
sf::Texture pinky_mov[2];
sf::Texture clyde_mov[2];
sf::Texture blinky_mov[2];
sf::Texture scared_ghost[2];
void load_textures(){
    pac_mov[0].loadFromFile("./pacman/0.png");
    pac_mov[1].loadFromFile("./pacman/1.png");
    pac_mov[2].loadFromFile("./pacman/2.png");

    inky_mov[0].loadFromFile("./ghosts/y-0.png");
    inky_mov[1].loadFromFile("./ghosts/y-1.png");

    pinky_mov[0].loadFromFile("./ghosts/p-0.png");
    pinky_mov[1].loadFromFile("./ghosts/p-1.png");

    clyde_mov[0].loadFromFile("./ghosts/b-0.png");
    clyde_mov[1].loadFromFile("./ghosts/b-1.png");

    blinky_mov[0].loadFromFile("./ghosts/r-0.png");
    blinky_mov[1].loadFromFile("./ghosts/r-1.png");

    scared_ghost[0].loadFromFile("./ghosts/f-0.png");
    scared_ghost[1].loadFromFile("./ghosts/f-1.png");
}

