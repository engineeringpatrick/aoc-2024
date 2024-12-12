#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream file("day3/day3.txt"); 

    int res = 0;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss{line};
            char c;
            std::string TEMPLATE = "mul(X,X)";
            int T_idx = 0;
            while (iss.get(c)) { 
                std::string num1 = "", num2 = "";
                if (TEMPLATE[T_idx] == 'X' && isdigit(c)) {
                    // std::cout << "here: " << c << std::endl;
                    while(iss && isdigit(c)) { num1 += c; iss.get(c); }
                    if(c != ',') { T_idx = 0; continue; }
                    iss.get(c);
                    while(iss && isdigit(c)) { num2 += c; iss.get(c); }
                    if(c != ')') { T_idx = 0; continue; }
                    
                    int n1 = stoi(num1), n2 = stoi(num2);
                    // std::cout << "adding: " << n1 << " * " << n2 << std::endl;
                    res += n1 * n2;
                    T_idx = 0;
                }
                else if (TEMPLATE[T_idx] != 'X' && TEMPLATE[T_idx] == c) { T_idx += 1; }
                else { T_idx = 0; }
            }
        }

        file.close();
    }

    std::cout << res << std::endl;
}