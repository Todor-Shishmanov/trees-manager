#pragma once
#include <vector> 
#include <string>

bool usable_file(std::string file_name);
bool is_digit(char c);
std::vector<std::string> separate(std::string line, char delimiter = ' ');
int stringToInt(std::string s);