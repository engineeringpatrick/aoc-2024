#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::vector<int>> readFile(const std::string& filename, std::unordered_map<int, std::unordered_set<int>>& prerequisites) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> updates;
    std::string line;
    
    while (std::getline(file, line)) {
        if(line == "") break;
        std::istringstream iss{line}; 
        std::string n1_str, n2_str; 
        std::getline(iss, n1_str, '|');
        std::getline(iss, n2_str, '|');
        int n1 = stoi(n1_str), n2 = stoi(n2_str);

        prerequisites[n2].insert(n1);
    }

    while (std::getline(file, line)) {
        std::istringstream iss{line}; 
        std::string number;
        std::vector<int> update;
        while (std::getline(iss, number, ',')) {
            update.push_back(stoi(number));
        }
        updates.push_back(update);
    }
    
    return updates;
}

int getSum(std::vector<std::vector<int>> updates, std::unordered_map<int, std::unordered_set<int>> prerequisites) {
    int res = 0;
    for(const auto& update: updates) {
        std::unordered_set<int> seen;
        std::unordered_set<int> presentPages{update.begin(), update.end()};
        bool isUpdateOrdered = true;
        for(const auto& page: update) {
            std::cout << "checking page: " << page << std::endl;
            if(!std::all_of(prerequisites[page].begin(), prerequisites[page].end(), [&seen, &presentPages](int n) { return !presentPages.contains(n) || seen.contains(n); })) {
                isUpdateOrdered = false;
                break;
            }
            seen.insert(page);
        }

        if(!isUpdateOrdered){
            std::vector<int> update_copy{update.begin(), update.end()};
            sort(update_copy.begin(), update_copy.end(), [&prerequisites](int a, int b){
                return prerequisites[b].contains(a);
            });
            res += update_copy[update_copy.size() / 2];
        }
    }
    return res;
}

int main() {
    std::unordered_map<int, std::unordered_set<int>> prerequisites;
    std::vector<std::vector<int>> updates = readFile("day5/test_input.txt", prerequisites);

    std::cout << getSum(updates, prerequisites) << std::endl;
    // for(const auto& [k, v] : prerequisites) { 
    //     std::cout << k << ": " << v.size() << std::endl;
    // }
    // for(const auto& update : updates) {
    //     for(const auto& n : update) {
    //         std::cout << n << ", ";
    //     }
    //     std::cout << std::endl;
    // }

}