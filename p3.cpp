#include <iostream> 
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

class Array{
    private:
        vector<string> s;
        vector<string> header;
        vector<vector<string>> arr;
    public:
        void print(ostream& out) {
            int c;
            for(c = 0; c < header.size() - 1; ++c) {
                out << header.at(c) << ",";
            }
            out << header.at(c) << endl;
            for(int i = 0; i < arr.size(); ++i) {
                for(int j = 0; j < arr.at(i).size() - 1; ++j) {
                    out << arr.at(i).at(j) << ",";
                }
                out << arr.at(i).at(arr.at(i).size() - 1) << endl;
            }
        }
        Array(ifstream& data) {
            string curr;
            string col;
            getline(data, curr);
            istringstream iss(curr);
            while (getline(iss, col, ',')) {
                header.push_back(col);
            }
            while (getline(data, curr)) {
                vector<string> g;
                istringstream iss(curr);
                while (getline(iss, col, ',')) {
                    g.push_back(col);
                }
                arr.push_back(g);
            }
        }
        void sot(ifstream& sor) {
            string curr;
            string col;
            while (getline(sor, curr)) {
                istringstream iss(curr);
                while (getline(iss, col, ',')) {
                    s.push_back(col);
                }
            }
            stable_sort(arr.begin(), arr.end(), [&](const vector<string> &a, const vector<string> &b) {
                return compare(a,b);
            });
        }
        bool compare(const vector<string> &a, const vector<string> &b) {
            for(int i = 0; i < s.size(); i += 3) {
                string colName = s.at(i);
                string order = s.at(i + 1);
                string dt = s.at(i + 2);
                if(dt == "string") {
                    for(int j = 0; j < header.size(); ++j) {
                        if(colName == header.at(j)) {
                            if(a.at(j) < b.at(j) && order == "ascend") return true;
                            else if(a.at(j) > b.at(j) && order == "ascend") return false;
                            else if(a.at(j) > b.at(j) && order == "descend") return true; 
                            else if(a.at(j) < b.at(j) && order == "descend") return false;
                        }
                    }
                }
                else if(dt == "int") {
                    for(int j = 0; j < header.size(); ++j) {
                        if(colName == header.at(j)) {
                            if(stoi(a.at(j)) < stoi(b.at(j)) && order == "ascend") return true;
                            else if(stoi(a.at(j)) > stoi(b.at(j)) && order == "ascend") return false;
                            else if(stoi(a.at(j)) > stoi(b.at(j)) && order == "descend") return true; 
                            else if(stoi(a.at(j)) < stoi(b.at(j)) && order == "descend") return false; 
                        }
                    }
                }
                else if(dt == "float") {
                    for(int j = 0; j < header.size(); ++j) {
                        if(colName == header.at(j)) {
                            if(stof(a.at(j)) < stof(b.at(j)) && order == "ascend") return true;
                            else if(stof(a.at(j)) > stof(b.at(j)) && order == "ascend") return false;
                            else if(stof(a.at(j)) > stof(b.at(j)) && order == "descend") return true; 
                            else if(stof(a.at(j)) < stof(b.at(j)) && order == "descend") return false; 
                        }
                    }
                }
                else return false;
            }
            return false;
        }

};

int main(int argc, char *argv[]) {
    ifstream data(argv[1]);
    ifstream sor(argv[2]);
    ofstream out(argv[3]);
    unsigned int i;

    Array arr(data);

    arr.sot(sor);

    arr.print(out);

    return 0;
}