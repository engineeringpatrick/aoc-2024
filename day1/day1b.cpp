#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

int main() {
    std::vector<int> list1, list2;
    std::ifstream file("day1.txt"); 

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss{line};
            int n1, n2;
            if(iss >> n1 >> n2){
                list1.push_back(n1);
                list2.push_back(n2);
            }
        }
        file.close();
    }

    std::unordered_set<int> list1_set(list1.begin(), list1.end());
    std::unordered_map<int, int> list2_count;
    for(const auto& n : list2) {
        if(list1_set.contains(n)) list2_count[n] += 1;
    }

    int res = 0;
    for(const auto& [val, cnt] : list2_count) res += val * cnt;
    std::cout << res << std::endl;
    
    return 0;
}