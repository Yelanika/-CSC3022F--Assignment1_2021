/***
 * Created Date: 2022/02/24
 * Yelanika Gunasekara
 * GNSSEN002
 * 
 * tag.cpp
 * 
 * ***/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int main (int argc, char* argv[]) {

    std::vector<std::string> tagInfo;
    std::string filename = "simple.txt";

    if (argc == 1)
        filename = "simple.txt";
    else
        filename = argv[1];

    std::ifstream in(filename);

    if(!in) {
        std::cout << "Couldn't open file" << filename << std::endl;
        return 1;
    }
    
    std::string line;
    while (std::getline(in, line)) {
        tagInfo.push_back(line);
    }

    in.close();

    std::cout << tagInfo.size() << std::endl;
    return 0;
}