#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> map;
    
    while (std::getline(file, line)) { map.push_back(line); }
    
    return map;
}

std::pair<int,int> findStartingCoords(const std::vector<std::string>& map) {
    for(int i = 0; i < map.size(); ++i) {
        for(int j = 0; j < map.size(); ++j) {
            if(map[i][j] == '^') return {i,j};
        }
    }
    return {0,0};
}


int getRouteLength(std::vector<std::string>& map, int x, int y) {
    const std::pair<int,int> dirs[] = {{-1,0},{0,1},{1,0},{0,-1}};
    int dirIdx = 0;
    int steps = 0;
    while(x >= 0 && x < map.size() && y >= 0 && y < map[x].size()) {
        if(map[x][y] != 'X') ++steps; // this check is needed because we could walk on already visited cells
        map[x][y] = 'X';
        if(map[x + dirs[dirIdx].first][y + dirs[dirIdx].second] == '#') dirIdx = (dirIdx + 1) % 4;
        x += dirs[dirIdx].first;
        y += dirs[dirIdx].second;
    }

    return steps;
}

int main() {
    std::vector<std::string> map = readFile("day6/test_input.txt");
    auto startCoords = findStartingCoords(map);
    std::cout << getRouteLength(map, startCoords.first, startCoords.second) << std::endl;
}