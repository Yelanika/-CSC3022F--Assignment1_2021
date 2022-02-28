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

/***
 * 
 * getTag -  
 * 
 * 
 * **/

std::string GNSSEN002::getTag(std::vector<std::string> tagInfo) {
    
    std::vector<std::string> tags;

    for (int i = 0; i < tagInfo.size(); ++i) {

        std::string temp = tagInfo[i];

        std::size_t SPos = temp.find("<");
        std::size_t EPos = temp.find(">");

        std::string tag = temp.substr(SPos,EPos-SPos);
        tags.push_back(tag);
    }
    std::cout << "Testing 1" << std::endl;
    return "Works";
    
}
    