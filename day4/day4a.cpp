#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> array2d;
    std::string line;
    
    while (std::getline(file, line)) {
        array2d.push_back(line);
    }
    
    return array2d;
}

int dfs(std::vector<std::string> matrix, int x, int y, std::string goal) {
    int res = 0;
    std::vector<std::pair<int,int>> dirs = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
    for(const auto& [dx, dy] : dirs) {
        int newx = x, newy = y;
        for(int i = 0; i < goal.size(); ++i) {
            if(newx < 0 || newx >= matrix.size() || newy < 0 || newy >= matrix[newx].size()) break;
            if(matrix[newx][newy] != goal[i]) { break; }
            if(i == goal.size() - 1) res += 1;
            newx += dx;
            newy += dy;
        }
    }

    return res;
}

int getCount(std::vector<std::string> matrix) {
    int res = 0;
    for(int i = 0; i < matrix.size(); ++i) {
        for(int j = 0; j < matrix[i].size(); ++j) {
            if(matrix[i][j] == 'X') { res += dfs(matrix, i, j, "XMAS"); }
            // wait im stupid lol we dont care about reverse else we'll double count 
            // if(matrix[i][j] == 'S') { res += dfs(matrix, i, j, "SAMX"); }
        }
    }
    return res;
}

int main() {
    std::vector<std::string> test_matrix = readFile("day4/test.txt");
    std::vector<std::string> input_matrix = readFile("day4/input.txt");
    for(const auto& str: test_matrix) std::cout << str << std::endl;

    std::cout << getCount(test_matrix) << std::endl;
    std::cout << getCount(input_matrix) << std::endl;
}