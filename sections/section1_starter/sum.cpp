/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */
#include <iostream>
#include <fstream>
#include "filelib.h"
#include "strlib.h"
#include "grid.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

/*
 * Sum Numbers (Code Write)
 * ----------------------------------
 * Write a program to read through a given file and sum
 * all of the numbers in the file. You can assume that numbers
 * will be composed entirely of numerical digits, optionally
 * preceded by a single negative sign.
 */
bool isNumber(string s) {
    if (s.length() > 0) {
        if (s[0] == '-') {
            s = s.substr(1);
        }
        for (char c : s) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int sumNumbers(string filename){
    // TODO: Your code here
    Vector<string> nums;
    ifstream stream;
    string curr = "";
    int total = 0;
    Vector<string> lines;
    openFile(stream, filename);
    readEntireFile(stream, lines);
    for (string &line : lines) {
        Vector<string> v = stringSplit(line, " ");
        for (string &s : v) {
            if (isNumber(s)) {
                total += stringToInteger(s);
            }
        }
    }
    return total;
}


/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("given file in handout"){
    EXPECT_EQUAL(sumNumbers("res/numbers.txt"), 42);
}

PROVIDED_TEST("Nonexistent file should sum to zero") {
    EXPECT_EQUAL(sumNumbers("nonexistent_filename"), 0);
}

