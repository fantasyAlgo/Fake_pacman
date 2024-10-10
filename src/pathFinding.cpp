#include "pathFinding.h"

std::pair<int, int> BFS(int map[][MAP_WIDTH], std::pair<int, int> start, std::pair<int, int> end){
    bool visited[MAP_HEIGHT][MAP_WIDTH];
    int distance[MAP_HEIGHT][MAP_WIDTH];
    int parent[MAP_HEIGHT][MAP_WIDTH];
    //memset(distance, 10000, sizeof(distance));
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            distance[i][j] = 10000;
            visited[i][j] = false;
            parent[i][j] = -1;
        }
    }

    if (map[start.second][start.first] == 1 || map[end.second][end.first] == 1){
        return std::make_pair(-1,-1);
    }
    distance[start.first][start.second] = 0;
    std::queue<std::pair<int, int>> queue;
    queue.push(start);
    std::pair<int, int> curr;
    std::pair<int, int> prevCurr;
    while (queue.size() > 0){
        curr = queue.front();
        //cout << "curr: " << curr.first << " " << curr.second <<  ", "<< distance[curr.first - 1][curr.second] << endl;
        queue.pop();
        if (curr.first == end.first && curr.second == end.second){
            while (curr.first != start.first || curr.second != start.second){
                prevCurr = curr;
                int temp = parent[curr.first][curr.second];
                curr.first = temp / MAP_WIDTH;
                curr.second = temp % MAP_WIDTH;
            }
            return prevCurr;
        }
        if (curr.first - 1 >= 0 && map[curr.second][curr.first - 1] == 0 && distance[curr.first - 1][curr.second] > distance[curr.first][curr.second] + 1){
            distance[curr.first - 1][curr.second] = distance[curr.first][curr.second] + 1;
            parent[curr.first - 1][curr.second] = curr.first * MAP_WIDTH + curr.second;
            queue.push(std::make_pair(curr.first - 1, curr.second));
        }
        if (curr.first + 1 < MAP_HEIGHT && map[curr.second][curr.first + 1] == 0 && distance[curr.first + 1][curr.second] > distance[curr.first][curr.second] + 1){
            distance[curr.first + 1][curr.second] = distance[curr.first][curr.second] + 1;
            parent[curr.first + 1][curr.second] = curr.first * MAP_WIDTH + curr.second;
            queue.push(std::make_pair(curr.first + 1, curr.second));
        }
        if (curr.second - 1 >= 0 && map[curr.second - 1][curr.first] == 0 && distance[curr.first][curr.second - 1] > distance[curr.first][curr.second] + 1){
            distance[curr.first][curr.second - 1] = distance[curr.first][curr.second] + 1;
            parent[curr.first][curr.second - 1] = curr.first * MAP_WIDTH + curr.second;
            queue.push(std::make_pair(curr.first, curr.second - 1));
        }
        if (curr.second + 1 < MAP_WIDTH && map[curr.second + 1] [curr.first]== 0 && distance[curr.first][curr.second + 1] > distance[curr.first][curr.second] + 1){
            distance[curr.first][curr.second + 1] = distance[curr.first][curr.second] + 1;
            parent[curr.first][curr.second + 1] = curr.first * MAP_WIDTH + curr.second;
            queue.push(std::make_pair(curr.first, curr.second + 1));
        }
    }
    return std::make_pair(-1,-1);
}

bool is_possible(std::pair<int, int> p){
    return p.first >= 0 && p.first < MAP_WIDTH && p.second >= 0 && p.second < MAP_HEIGHT;
}
std::pair<int, int> nearest_move(std::pair<int, int> obj){
    if (obj.first+1 < MAP_WIDTH && pacman_map[obj.first+1][obj.second] == 1)
        return std::make_pair(obj.first+1, obj.second);
    if (obj.first-1 >= 0 && pacman_map[obj.first-1][obj.second] == 1)
        return std::make_pair(obj.first-1, obj.second);
    if (obj.second+1 < MAP_HEIGHT &&  pacman_map[obj.first][obj.second+1] == 1)
        return std::make_pair(obj.first, obj.second+1);
    //if (obj.second-1 >= 0 && pacman_map[obj.first][obj.second-1] == 1)
    return std::make_pair(obj.first, obj.second-1);
}
