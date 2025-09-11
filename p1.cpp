#include <iostream> 
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream InFile(argv[1]);
    ofstream OutFile(argv[2]);
    string line;
    vector<string> sources;
    vector<string> dest;
    vector<int> bands;
    vector<string> singles;


    while(getline(InFile, line)) {
        istringstream iss(line);
        string sourceName;
        iss >> sourceName;
        sources.push_back(sourceName);
        string destName;
        iss >> destName;
        dest.push_back(destName);
        int bandwidth;
        iss >> bandwidth;
        bands.push_back(bandwidth);
    }
    unsigned int i;
    unsigned int j;
    for(i = 0; i < sources.size(); ++i) {
        for(j = 0; j < sources[i].length(); ++j) {
            sources[i][j] = toupper(sources[i][j]);
        }
        for(j = 0; j < dest[i].length(); ++j) {
            dest[i][j] = toupper(dest[i][j]);
        }
    }


    for(i = 0; i < sources.size(); ++i) {
        singles.push_back(sources[i]);
        for(j = 0; j < singles.size() - 1; ++j) {
            if(sources[i] == singles[j]) singles.pop_back();
        }
        singles.push_back(dest[i]);
        for(j = 0; j < singles.size() - 1; ++j) {
            if(dest[i] == singles[j]) singles.pop_back();
        }
    }
    for(i = 0; i < singles.size(); ++i) {
        OutFile << singles[i] << endl;
    }
    OutFile << endl;

    bool insource = false;
    bool indest = false;
    int srcBand = 0;
    int destBand = 0;
    double ratio;
    for(i = 0; i < singles.size(); ++i) {
        for(j = 0; j < sources.size(); ++j) {
            if(singles[i] == sources[j]) {
                srcBand += bands[j];
                insource = true;
            }
            if(singles[i] == dest[j]) {
                destBand += bands[j];
                indest = true;
            }
        }
        if(indest && insource) {
            ratio = (double)destBand / srcBand;
            OutFile << singles[i] << " " << srcBand << " " << destBand << " ";
            OutFile << fixed << setprecision(2) << ratio << endl;
        }
        srcBand = 0;
        destBand = 0;
        insource = false;
        indest = false;
    }
    


    OutFile.close();
    InFile.close();
    return 0;
}