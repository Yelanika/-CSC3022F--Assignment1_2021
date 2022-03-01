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
        std::cout << StagPos << " " << i << std::endl;
        std::size_t EtagPos = temp.find(">");

        std::string tag = temp.substr(StagPos,EtagPos-StagPos+1);
       // std::cout << tag << std::endl;
        tags.push_back(tag);

        //Getting the text
        temp = temp.substr(EtagPos+1);

        std::size_t StextPos = temp.find("<");
        std::size_t EtextPos = temp.find(">");

        std::string tText = temp.substr(0,StextPos);
       // std::cout << tText << std::endl;
        text.push_back(tText);
    }

    std::vector<GNSSEN002::TagStruct> Tag;
    

    Tag.push_back({tags[0], 1, text[0]});

    if (tags.size() > 1) {
        for (int i = 1; i < tags.size(); ++i) {
            
            bool found = false;
            int k_tag;

            //search for the same tag
            for (k_tag = 1; k_tag < tags.size(); ++k_tag) {

                //condition: to not check same tag against each other
                if ((k_tag-1) != i) {
                    if (tags[i] == tags[k_tag-1]) {
                        found = true;
                        break;      //break out of loop
                    }
                }
            }

            if (found)  {       //if found is true
                Tag[k_tag-1].tagName = tags[k_tag-1];
                Tag[k_tag-1].noTagPairs++;
                Tag[k_tag-1].tagText += " : " + text[k_tag-1];
            }
            else                //if a new tag name is found
                Tag.push_back({tags[i], 1, text[i]});  
        }
    }

    for (int j = 0; j < Tag.size(); ++j) {
        std::cout << Tag[j].tagName << std::endl;
        std::cout << Tag[j].noTagPairs << std::endl;
        std::cout << Tag[j].tagText << std::endl;
    }



    std::cout << "Testing 2" << std::endl;
    return "";
    
}
    