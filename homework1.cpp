#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

/*
 Name: Chad Bynum
 Email: ccbynum@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 1
 compile command: g++ homework1.cpp
 ./a.out inputX.txt
 Serial Number: 49
*/

int main(int argc, char** argv) { 
    std::ifstream fin(argv[1]);
    std::string word;
    std::map<std::string, int> wordCount;
    while (fin >> word) { 
        ++wordCount[word]; 
    } 

    std::vector<std::pair<std::string,int>> vec(wordCount.begin(), wordCount.end());
    std::sort(vec.begin(), vec.end(),
        [](const auto &a, const auto &b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    
    for (const auto &p : vec) {
        std::cout << p.first << ": " << p.second << '\n';
    }
    return 0;
}