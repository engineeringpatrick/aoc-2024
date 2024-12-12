#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream file("day2/day2.txt"); 

    int res = 0;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss{line};
            std::vector<int> nums;
            int prev, curr;
            while(iss >> curr) { nums.push_back(curr); }

            // bruteforce this shit
            for (int i = 0; i < nums.size(); ++i) {
                std::cout << nums[i] << " ";
                int bad_levels = 0;
                int prev = -1, curr = -1;
                bool has_inc = false;
                bool inc = false;
                for (int j = 0; j < nums.size(); ++j) {
                    if(i == j) continue;
                    if(prev == -1) { prev = nums[j]; continue; }
                    curr = nums[j];
                    
                    if(has_inc && (prev >= curr && inc || prev <= curr && !inc) || abs(curr - prev) > 3 || abs(curr - prev) == 0) { 
                        bad_levels++;
                    }
                    else if(!has_inc) {
                        has_inc = true;
                        inc = prev < curr;
                    }
                    prev = curr;
                }

                if(bad_levels < 1) {
                    res++;
                    break;
                }
            }
            std::cout << std::endl;
        }

        file.close();
    }

    std::cout << res << std::endl;
}