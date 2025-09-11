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

template <typename RandomIt>

constexpr void merge(RandomIt first, RandomIt mid, RandomIt last, RandomIt tempstart) {
    RandomIt left = first;
    RandomIt right = mid;
    RandomIt temp = tempstart;

    while (left != mid && right != last) {
        if (*left <= *right) {
            *temp++ = *left++;
        } else {
            *temp++ = *right++;
        }
    }

    temp = std::copy(left, mid, temp);
    temp = std::copy(right, last, temp);

    std::copy(tempstart, temp, first);
}

template <typename RandomIt>
constexpr void mergesort(RandomIt first, RandomIt last, RandomIt tempstart) {
    auto distance = std::distance(first, last);
    if (distance <= 1) return;

    RandomIt mid = first;
    std::advance(mid, distance / 2);

    mergesort(first, mid, tempstart);
    mergesort(mid, last, tempstart);

    merge(first, mid, last, tempstart);
}