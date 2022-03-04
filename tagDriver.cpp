/***
 * Created Date: 2022/02/24
 * Yelanika Gunasekara
 * GNSSEN002
 * 
 * tag.cpp
 * 
 * ***/

#include "tag.h"
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
    //std::cout << "1" << filename << std::endl;
    if(!in) {
        std::cout << "Couldn't open file" << filename << std::endl;
        return 1;
    }
    //std::cout << "2" << filename << std::endl;
    std::string line;
    while (std::getline(in, line)) {
        tagInfo.push_back(line);
    }

    in.close();

    //std::cout << "3" << filename << std::endl;

    if (tagInfo.size() > 0) {
    //std::cout << "4" << filename << std::endl;
        GNSSEN002::ExtractTagsandText(tagInfo);
        //std::cout << "5" << filename << std::endl;
    }
    else    
        std::cout << "There is no data in the file provided: " << filename << std::endl;
    //std::cout << tagInfo.size() << std::endl;
    return 0;
}