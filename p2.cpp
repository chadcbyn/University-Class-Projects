#include <iostream> 
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

bool Eq(string que, string vecWord) {
    if(que == "" && vecWord == "") return true;
    else if(que == "") return false;
    else if(que[0] == vecWord[0]) return Eq(que.substr(1),vecWord.substr(1));
    else if (que[0] == '?') return (vecWord != "" && Eq(que.substr(1), vecWord.substr(1))) || Eq(que.substr(1), vecWord);
    else return false;
}

int main(int argc, char *argv[]) {
    ifstream file(argv[1]);
    unsigned int i;
    int numWords = 0;
    vector<string> words;
    string word;
    vector<int> arr;
    vector<string> matches;
    while(file >> word) {
        for(i = 0; i < word.length(); ++i) {
            if(!isalpha(word.at(i))) {
                word[i] = ' ';
            }
        }
        stringstream ss(word);
        string wordd;
        while(ss >> wordd) {
            for(i = 0; i < wordd.length(); ++i) {
                wordd[i] = tolower(wordd[i]);
            }
            numWords++;
            bool in = false;
            for(i = 0; i < words.size(); ++i) {
                if(words.at(i) == wordd) {
                    in = true;
                    arr[i]++;
                }
            }
            if(!in) {
                words.push_back(wordd);
                arr.push_back(1);
            }
        }
    }
    cout << "The number of words found was " << numWords << endl;
    cout << "The number of distinct words was " << words.size() << endl;
    string input;
    bool match = false;
    while(input != "STOP") {
        cout << endl;
        cout << "Enter a word:" << endl;
        cin >> input;
        if(input != "STOP") {
            for(i = 0; i < words.size(); ++i) {
                if(Eq(input, words[i])) {
                    cout << "The word " << words[i] << " appears " << arr[i] << " times" << endl;
                    match = true;
                }
            }
            if(!match) cout << "The word " << input << " appears 0 times" << endl;
            match = false;
        }
    }
}