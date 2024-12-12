#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

std::vector<std::string> splitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> res;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while(end != std::string::npos) {
        res.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }

    res.push_back(str.substr(start)); // add the rest of the string back
    return res;
}

int part1(const std::string& str) {
    std::vector<std::string> after_mul = splitString(str, "mul(");
    
    int res = 0;
    for(int i = 1; i < after_mul.size(); ++i) {
        std::vector<std::string> inside_parentheses = splitString(after_mul[i], ")");
        if(inside_parentheses.empty()) continue;

        std::vector<std::string> numbers = splitString(inside_parentheses[0], ",");
        if(numbers.size() != 2) continue;

        auto is_number = [](char c) { return isdigit(c); };
        if(!std::all_of(numbers[0].begin(), numbers[0].end(), is_number) || !std::all_of(numbers[1].begin(), numbers[1].end(), is_number)) continue;

        res += std::stoi(numbers[0]) * std::stoi(numbers[1]);    
    }

    return res;
}

std::string preprocess(const std::string& str) {
    std::vector<std::string> after_dont = splitString(str, "don't()");
    if(after_dont.empty()) return "";
    std::string do_string = after_dont[0];

    for(int i = 1; i < after_dont.size(); ++i) {
        std::vector<std::string> after_dos = splitString(after_dont[i], "do()"); 
        // we know that every one of these after idx 0 is valid. because they're inbetween a do and a dont

        for(int j = 1; j < after_dos.size(); ++j) {
            do_string += after_dos[j];
        }
    }

    return do_string;
}

int part2(const std::string& str) {
    std::string do_str = preprocess(str);
    return part1(do_str);
}

int main() {
    std::string input_str = readFile("day3/day3.txt");
    std::cout << part1(input_str) << "\n";
    std::cout << part2(input_str) << "\n";
}