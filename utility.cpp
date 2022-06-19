#include "utility.h"
#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

//Checks if such a file already exist and whether the program has access rights.
bool usable_file(std::string file_name) {
    std::ifstream infile(file_name.c_str());
    return infile.good();
}

bool is_digit(char c) {
    if (c <= '9' && c >= '0') return true;
    return false;
}

std::vector<std::string> separate(std::string line, char delimiter) {
    std::string curr;
    std::vector<std::string> separated;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == delimiter) {
            separated.push_back(curr);
            curr.clear();
            continue;
        }
        curr += line[i];
    }
    separated.push_back(curr);
    return separated;
}

int stringToInt(string s) {
    int number = 0;
    bool negative = false;
    if (s[0] == '-') {
        negative = true;
        s.erase(s.begin() + 0);
    }
    for (size_t i = 0; i < s.length(); i++) {
        number *= 10;
        number += s[i] - '0';
    }
    if (negative) number *= -1;
    return number;
}
