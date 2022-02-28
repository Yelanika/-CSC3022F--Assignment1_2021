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

std::string GNSSEN002::ExtractTagsandText(std::vector<std::string> tagInfo) {
    
    std::vector<std::string> tags;
    std::vector<std::string> text;

    std::cout << "Testing 1" << std::endl;  

    for (int i = 0; i < tagInfo.size(); ++i) {

        std::string temp = tagInfo[i];

        //Getting the tag
        std::size_t StagPos = temp.find("<");
        std::size_t EtagPos = temp.find(">");

        std::string tag = temp.substr(StagPos,EtagPos-StagPos+1);
        std::cout << tag << std::endl;
        tags.push_back(tag);

        //Getting the text
        temp = temp.substr(EtagPos+1);

        std::size_t StextPos = temp.find("<");
        std::size_t EtextPos = temp.find(">");

        std::string tText = temp.substr(0,StextPos);
        std::cout << tText << std::endl;
        text.push_back(tText);
    }

    //std::cout << "Testing 1" << std::endl;
    return "";
    
}
    