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
#include <sstream>
#include <cctype>
#include <algorithm>

/***
 * 
 * getTag -  
 * 
 * 
 * **/

std::string GNSSEN002::ExtractTagsandText(std::vector<std::string> tagInfo) {
    
    std::vector<std::string> tags;
    std::vector<std::string> text;

    //std::cout << "Testing 1" << std::endl;  

    for (int i = 0; i < tagInfo.size(); ++i) {

        std::string temp = tagInfo[i];

        //variables to help identify if the line has any values or is empty 
        std::string temp2 = temp;
        //temp2.erase(std::remove(temp2.begin(),temp2.end(),::isspace));
        //std::cout << temp2 << std::endl;
        int spaces = 0;

        for (int j = 0; j < temp2.length(); ++j) {
            if (temp2.at(j) == ' ')
                spaces++;
        }

        bool found_endTag = false; //to check if the end tag is found first
        //if the no. of spaces in the line = length of the line-1, then go to next line
        if (spaces == (temp2.length()-1))
            continue;
        else {              //else capture the data in the line

            //Getting the tag
            std::size_t StagPos = temp.find("<");

            //if there is a tag in the current line
            if (StagPos!=std::string::npos) {
                //std::cout << StagPos << " " << i << std::endl;

                std::size_t EndTagPos = temp.find("/");

                if (EndTagPos!=std::string::npos) //if an endtag is found
                    continue;
                else {     
                std::size_t EtagPos = temp.find(">");

                std::string tag = temp.substr(StagPos,EtagPos-StagPos+1);
                //std::cout << tag << std::endl;
                tags.push_back(tag);

                //current line without the tag
                temp = temp.substr(EtagPos+1);  
                //std::cout << temp << " " << EtagPos << std::endl;
                }
            }
            
            //Getting the text - looking for end tag
            std::size_t StextPos = temp.find("<");

            //if end tag is found & we are getting the text
            if (StextPos!=std::string::npos) {
                std::size_t EtextPos = temp.find(">");

                std::string tText = temp.substr(0,StextPos);
                //std::cout << tText << " " << StextPos << std::endl;
                text.push_back(tText);
            }
            else    //else there must only be string left in the current line 
                text.push_back(temp);
        }
        
    }

    //std::cout << "Testing 2" << std::endl;
    std::vector<GNSSEN002::TagStruct> Tag;
    //std::cout << "Testing 2" << std::endl;
    

    Tag.push_back({tags[0], 1, text[0]});

    if (tags.size() > 1) {
        for (int i = 1; i < tags.size(); ++i) {
            
            bool found = false;
            int k_tag;

            std::cout << tags[i] << " " << text[i] << std::endl;

            //search for the same tag
            for (k_tag = 1; k_tag < i+1; ++k_tag) { //k_tag = position of the tag in vector

                //condition: to not check same tag against each other
                if ((k_tag-1) != i) {
                    if (tags[i] == tags[k_tag-1]) {
                        found = true;
                        break;      //break out of loop
                    }
                }
            }
            
            if (found)  {       //if found is true
               // Tag[k_tag-1].tagName = tags[k_tag-1];
               // std::cout << "FOUND" << std::endl;
               // std::cout << i << " - " << text[i] << std::endl;

                Tag[k_tag-1].noTagPairs++;
                Tag[k_tag-1].tagText += " : " + text[i];
                //std::cout << Tag[k_tag-1].tagText << " - " << text[k_tag-1] << std::endl;
            }
            else                //if a new tag name is found
                Tag.push_back({tags[i], 1, text[i]});  

            //std::cout << "End of loop" << std::endl;
        }

    }
    //std::cout << "Testing 4" << std::endl;
    // for (int j = 0; j < Tag.size(); ++j) {
    //     std::cout << Tag[j].tagName << std::endl;
    //     std::cout << Tag[j].noTagPairs << std::endl;
    //     std::cout << Tag[j].tagText << std::endl;
    // }

    std::cout << "Testing Passed" << std::endl;
    return "";
    
}
    