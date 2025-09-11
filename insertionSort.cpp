#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

/*
 Name: Chad Bynum
 Email: ccbynum@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 0
*/

template< class RandomIt >
constexpr void insertionsort ( RandomIt first, RandomIt last ) {
    for(RandomIt i = std::next(first); i != last; ++i) {
        auto key = *i;
        RandomIt j = i;

        while(j != first && *std::prev(j) > key) {
            *j = *std::prev(j);
            --j;
        }
        *j = key;
    }
}