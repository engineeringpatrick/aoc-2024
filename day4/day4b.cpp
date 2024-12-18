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

bool dfs(std::vector<std::string> matrix, int x, int y, std::string goal, bool leftToRight) {
    for(int i = 0; i < goal.size(); ++i) {
        if(x < 0 || x >= matrix.size() || y < 0 || y >= matrix[x].size()) break;
        if(matrix[x][y] != goal[i]) { break; }
        if(i == goal.size() - 1) return true;
        x++;
        y += 1 * (leftToRight ? 1 : -1);
    }
    return false;
}

int getCount(std::vector<std::string> matrix) {
    int res = 0;
    for(int x = 0; x < matrix.size(); ++x) {
        for(int y = 0; y < matrix[x].size(); ++y) {
            if((dfs(matrix, x, y, "MAS", true) || dfs(matrix, x, y, "SAM", true)) && (dfs(matrix, x, y+2, "MAS", false) || dfs(matrix, x, y+2, "SAM", false))) ++res;
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