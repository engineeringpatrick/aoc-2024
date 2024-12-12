#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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


    int res = 0;
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    for(int i = 0; i < list1.size(); ++i) { res += abs(list1[i] - list2[i]); }
    std::cout << res << std::endl;
}