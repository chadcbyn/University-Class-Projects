#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>

#include "ST.hpp"
#include "RBTPrint.hpp"

/*
 Name: Chad Bynum
 Email: ccbynum@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 2
 compile command: g++ STMain.cpp
 ./a.out inputX.txt
 Serial Number: 49
*/

int main(int argc, char *argv[]) {
	std::ifstream fin(argv[1]);
    ST<std::string, int> st;
    std::string word;
	int words = 0;
    while (fin >> word) { 
         st[word]++;
		 words++;
    }

    // get contents of symbol table as vector
    auto vec = st.toVector();
    auto start = std::chrono::high_resolution_clock::now();

    // sort by descending value, then descending key (alphabetical) on ties
    std::sort(vec.begin(), vec.end(), [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b){
        if (a.second != b.second) return a.second > b.second; // larger counts first
        return a.first < b.first; // descending alphabetical order
    });
    auto end = std::chrono::high_resolution_clock::now();

    // print sorted pairs
    for (const auto &p : vec) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << "Distinct words: " << st.GetLength() << std::endl;

	return 0;
}
