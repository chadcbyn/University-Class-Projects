// Sample program that reads a "/" delimited file and a query file and
// prints the parsed concents to stdout


/*
 Name: Chad Bynum
 Email: ccbynum@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 3
 To Compile: g++ HW3Sample.cpp
 To Run: ./a.out dbfile1.txt query.txt
*/


#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <algorithm>


static inline std::string trim(const std::string &s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}


int main(int argc, char *argv[]) {
    // check for correct command-line arguments
    if (argc != 3) {
       std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
       return 1;
    }


    std::ifstream dbfile(argv[1]);
    if (!dbfile.is_open()) {
       std::cout << "Unable to open file: " << argv[1] << std::endl;
       return 1;
    }


    // Use unordered_maps for O(1) average lookup time
    std::unordered_map<std::string, std::unordered_set<std::string>> movieToActors;
    std::unordered_map<std::string, std::unordered_set<std::string>> actorToMovies;


    std::string line;
    while (std::getline(dbfile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;


        // first token is the movie
        if (!std::getline(ss, token, '/')) continue;
        std::string movie = trim(token);
        if (movie.empty()) continue;


        // remaining tokens are actors
        while (std::getline(ss, token, '/')) {
            std::string actor = trim(token);
            if (actor.empty()) continue;
            movieToActors[movie].insert(actor);
            actorToMovies[actor].insert(movie);
        }
    }
    dbfile.close();


    std::ifstream queryfile(argv[2]);
    if (!queryfile.is_open()) {
       std::cout << "Unable to open file: " << argv[2] << std::endl;
       return 1;
    }


    std::string query;
    while (std::getline(queryfile, query)) {
        query = trim(query);
        if (query.empty()) continue;


        auto mit = movieToActors.find(query);
        if (mit != movieToActors.end()) {
            // query is a movie: print all actors
            for (const auto &actor : mit->second) {
                std::cout << actor << std::endl;
            }
            continue;
        }


        auto ait = actorToMovies.find(query);
        if (ait != actorToMovies.end()) {
            // query is an actor: print all movies
            for (const auto &mv : ait->second) {
                std::cout << mv << std::endl;
            }
            continue;
        }


        std::cout << "Not Found" << std::endl;
    }
    queryfile.close();


    return 0;
}
