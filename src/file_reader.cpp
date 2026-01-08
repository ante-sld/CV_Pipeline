#include "file_reader.h"
#include <fstream>
#include <iostream>

void read_file(const char* fileName, std::string& config) {
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line)) {
        config += line + "\n";   // \n added to keep new line consistency
    }
}
