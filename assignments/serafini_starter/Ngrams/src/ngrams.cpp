// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "map.h"
#include "simpio.h"

using namespace std;

bool isNumber(string s) {
    for (char c : s) {
        if (isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    // TODO: Finish the program!
    ifstream stream;
    string filename;
    int N;
    int word_num;
    Map<Vector<string>, Vector<string>> ngram_map;
    filename = promptUserForFile(stream, "Input file name?");
    while (1) {
     string line = getLine("Value of N?(Should be positive)");
     if (!isNumber(line)) {
         cout << "Illegal integer format. Try again." << endl;
         continue;
     }
     N = stringToInteger(line);
     if (N < 2) {
         cout << "N must be 2 or greater." << endl;
         continue;
     }
     break;
    }



    while (1) {
        cout << endl;
        string line = getLine("# of random words to generate (0 to quit)?");
        if (!isNumber(line)) {
            cout << "Illegal integer format. Try again." << endl;
            continue;
        }
        word_num = stringToInteger(line);
        if (word_num == 0) {
            break;
        }
        if (word_num < N) {
            cout << "Must be at least " << N << " words." << endl;
            continue;
        }
        string word;
        Vector<string> key;
        Vector<string>first_gram;
        int count = N-1;
        for (int i = 0; i < N-1; i++) {
            string word;
            stream >> word;
            first_gram.add(word);
        }
        key = first_gram;
        while (stream >> word) {
            // each time through this loop, word is the next word in the file
            if (count == N-1) {
                ngram_map[key].add(word);
                key.remove(0);
                count = N-2;
            }
            key.add(word);
            count++;
        }
        for (int i = 0; i < N-1; i++) {
            ngram_map[key].add(first_gram[i]);
            key.remove(0);
            key.add(first_gram[i]);
        }
        Vector<Vector<string>>grams = ngram_map.keys();
        int index = randomInteger(0, grams.size()-1);
        Vector<string>gram = grams[index];
        cout << "... ";
        for (int i = N-1; i < word_num; i++) {
            cout << gram[0] << " ";
            Vector<string> key = ngram_map[gram];
            index = randomInteger(0, key.size()-1);
            gram.remove(0);
            gram.add(key[index]);
        }
        for (string& word: gram) {
            cout << word << " ";
        }
        cout << "..." << endl;
    }

    cout << "Exiting." << endl;
    return 0;
}
