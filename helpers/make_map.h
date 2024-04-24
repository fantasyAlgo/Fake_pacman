vector<sf::RectangleShape> build_map(){
    vector<sf::RectangleShape> map;
    // little optimization
    int width;
    cout << width_ratio << endl;
    for (int i = 0; i < MAP_HEIGHT; i++){
        width = width_ratio;
        for (int j = 0; j < MAP_WIDTH; j++){
            if (pacman_map[i][j] == 1 && j+1 < MAP_WIDTH && pacman_map[i][j+1] == 1){
                width += width_ratio;
            } else if (pacman_map[i][j] == 1) {
                sf::RectangleShape rect(sf::Vector2f(width, height_ratio));
                rect.setPosition(j*width_ratio - width + width_ratio, i*height_ratio);
                rect.setSize(sf::Vector2f(width, height_ratio));
                rect.setFillColor(sf::Color::Blue);
                map.push_back(rect);
                width = width_ratio;
            }
        }
    }
    return map;
}
vector<Coin> make_coins(){
    vector<Coin> coins;
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (pacman_map[i][j] == 0){
                Coin coin(width_ratio/6, make_pair(j, i));
                coin.setFillColor(sf::Color::Yellow);
                coin.setPosition(j*width_ratio + width_ratio/2, i*height_ratio + height_ratio/2);
                coins.push_back(coin);
            }
        }
    }
    return coins;
}

vector<POWER_UP> make_power(){
    vector<POWER_UP> power;
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (pacman_map[i][j] == 2){
                POWER_UP coin(width_ratio/4, make_pair(j, i));
                coin.setFillColor(sf::Color::Yellow);
                coin.setPosition(j*width_ratio + width_ratio/2, i*height_ratio + height_ratio/2);
                power.push_back(coin);
            }
        }
    }
    return power;
}
