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

//namespace GNSSEN002 {
    /***
     * * ExtractTagsandText():
     *      ` 
     * 
     * **/
    void GNSSEN002::ExtractTagsandText(std::vector<std::string> tagInfo) {
        
        std::vector<std::string> tags;
        std::vector<std::string> text; 
        int no_nestedTag = 0; 
        int tagCounter = 0;
        bool sameLine = false;
        int max_no_nestedTag = 0;
        int tagIndex = -1;
        std::vector<int> no_tagPairs;

        for (int lineNo = 0; lineNo < tagInfo.size(); ++lineNo) {      //going through each line of the textfile

            std::string TagInfo_currentLine = tagInfo[lineNo];    

            bool found_ClosingTag = false; //to check if the end tag is found first

            std::size_t TagPos_Start = -1;

            if ((TagInfo_currentLine.length()) == 0)       //line is empty
                //ends this iteration and goes to the next iteration
                continue;
            else {              //else capture the data in the line

                char action = 'a';  //the action that will take place in the below switch statement
                
                bool notEmpty = true;
                bool tagInText = false;

                
                //for loop going through each line
                //nestedTag_no                
                while(notEmpty) {
                    switch(action) {
                        case 'a' : {    //option = assign
                            std::cout << lineNo << " Assign: " << TagInfo_currentLine << std::endl;
                            if (TagInfo_currentLine.length() == 0)  {       //if line is empty
                                notEmpty = false;
                                std::cout << " " <<std::endl;
                                // std::cout << tags[tagCounter-1] << " " << text[tagCounter-1] << std::endl;
                                // std::cout << " " <<std::endl;
                                break;
                                //continue;
                            }
                            else {
                                TagPos_Start = TagInfo_currentLine.find("<");                                

                                //if there is a tag in the current line
                                if (TagPos_Start != std::string::npos) {

                                    if (TagPos_Start == 0) {    //if tag is in the first position
                                    //if (counter == 0)
                                        action = 'b';//option:tag
                                        break;
                                    }
                                    else {          // else text is before tag
                                        tagInText = true;
                                        action = 'c';   //option text
                                        break;
                                    }
                                }
                                else {  //there is no tag in the line, just text
                                    sameLine = true;
                                    action ='c';
                                    break;
                                }
                            }
                            break;
                        }
                        case 'b' : {    //option = tag
                            std::cout << lineNo << " Tag: " << TagInfo_currentLine << std::endl;
                            //Checking for the beginning of a tag
                            //TagPos_Start = TagInfo_currentLine.find("<");

                            //if there is a tag in the current line
                            if (TagPos_Start != std::string::npos) {
            
                                std::size_t TagPos_End = TagInfo_currentLine.find(">");   //finding the end of the tag 
                                //if (TagPos_End != std::string::npos)
                                    //action =  'c';
                                    //breakk;????
                                std::string tag = TagInfo_currentLine.substr(TagPos_Start,TagPos_End-TagPos_Start+1); 

                                //put code here
                                bool inner_bracket = true;
                                std::size_t test_tag_open = -1;
                                std::string test_tag = tag.substr(1,tag.size());

                                while (inner_bracket) {

                                    test_tag_open = test_tag.find("<");
                                    if (test_tag_open != std::string::npos) {
                                        test_tag = test_tag.substr(test_tag_open+1,test_tag.size());
                                        tagInText = true;
                                        sameLine = true;
                                        TagPos_Start = test_tag_open;
                                        action = 'c';
                                    }
                                    else {
                                        inner_bracket = false;
                                    }
                                }

                                if (tagInText == true) {
                                    
                                    break;
                                }

                                //if only tag left in the current line
                                std::size_t find_ClosingTag = tag.find("/");    //check if tag is a closing tag
                                if (find_ClosingTag != std::string::npos) {
                                    // if (no_nestedTag > 1) {
                                    //     if (max_no_nestedTag < no_nestedTag)
                                    //         max_no_nestedTag = no_nestedTag;
                                    // }
                                    no_nestedTag--;
                                    sameLine = false;
                                    // if (no_nestedTag == 0) 
                                    //     max_no_nestedTag = 0;
                                   
                                    
                                }
                                else {            //opening tag
                                    for (int check_SameTag = 0; check_SameTag < tags.size(); ++check_SameTag) {
                                        if (tag == tags[check_SameTag]) {
                                            
                                            tagIndex = check_SameTag;
                                            no_tagPairs[tagIndex]++;
                                            std::cout << lineNo << " Tag: " << tag << " tag index: " << tagIndex << " check_sametag: " << check_SameTag << std::endl;
                                            break;
                                        }
                                        else{
                                            
                                            tagIndex = - 1;
                                            //std::cout << lineNo << " Tag: " << tag << " tag index: " << tagIndex << std::endl;
                                            //break;
                                        }
                                        
                                    }
                                    if (tagIndex == -1) {
                                        tags.push_back(tag);
                                        no_tagPairs.push_back(1);
                                    }

                                    std::cout << lineNo << " Tag: " << tag << " tag index: " << tagIndex << std::endl;
                                    //tags.push_back(tag);
                                    tagCounter++;
                                    no_nestedTag++;
                                }
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_End+1); 
                                //std::cout << lineNo << " Tag: no_nestedTag: " << no_nestedTag << " tag index: " << tagIndex << std::endl;
                                //if (tagIndex == -1)
                                    //action = 'c';
                                    //break;
                            }
                            action = 'a';    //option = assign
                            break;
                        }
                        case 'c' : {    //option = text
                            std::cout << lineNo << " Text: " << TagInfo_currentLine << std::endl;
                            std::string tagInfo = "";

                            //if (TagInfo_currentLine == "")
                                //text.pushback("");
                                //action = 'a';
                                //break;

                            if (tagInText == true) {     //there is a tag after the text
                                //std::size_t TagPos_Start = TagInfo_currentLine.find("<");       //comment out
                               // std::cout << lineNo << " Text: inside loop" << std::endl;
                                tagInfo = TagInfo_currentLine.substr(0,TagPos_Start);
                               // std::cout << lineNo << " Text: " << tagInfo << std::endl;
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_Start);
                                //std::cout << lineNo << " Text: " << TagInfo_currentLine << std::endl;
                            }
                            else { //no tag in text
                                tagInfo = TagInfo_currentLine;
                                //std::cout << "Error 1" << std::endl;
                                TagInfo_currentLine = TagInfo_currentLine.substr(tagInfo.size());
                               // std::cout << "Error 2" << std::endl;
                            }

                            //check for tab spaces
                            bool tabFound = true;
                            

                            while (tabFound) {
                                if (tagInfo[0] == '\t') 
                                    tagInfo = tagInfo.substr(1, tagInfo.size());
                                else
                                    tabFound = false;
                            }

                            std::cout << lineNo << " Text: " << tagInfo << " tag index: " << tagIndex << " sameline: " << sameLine << std::endl;
                            //comment out
                            // if ((no_nestedTag == 1) and (sameLine == false))  {
                            //     text.push_back(tagInfo);
                            //     sameLine = true;
                            // }
                            if (tagIndex == -1) {
                                text.push_back(tagInfo);
                                tagIndex = text.size() -1; 
                            }
                            else if ((sameLine == true)) {
                            // else if ((no_nestedTag == 1) and (sameLine == true)) {
                                //text[tagCounter - 1] += " " + tagInfo;
                                text[tagIndex] += " " + tagInfo;
                            }
                            
                            else {  //text not in the sameLine and there is an tagIndex
                               // std::cout << "Error 3" << std::endl;
                                //text[tagCounter - no_nestedTag] += tagInfo;
                                text[tagIndex] += " : " + tagInfo;
                                std::cout << lineNo << " Text: " << text[tagIndex] << std::endl;
                               // std::cout << "Error 4" << std::endl;
                            }
                            std::cout << lineNo << " Text: " << tagInfo << std::endl;
                            tagInText = false;
                            action = 'a';   //option = assign
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        if (tags.size() == text.size() and (tags.size() == no_tagPairs.size())) { 
            for (int i = 0; i < tags.size(); ++i) {
                std::cout << "Tag: " << tags[i] << " pairs: " << no_tagPairs[i] << " Text: " << text[i] << std::endl;
                Tag.push_back({tags[i], no_tagPairs[i], text[i]});
            }
        }
        else 
            std::cout << "Error: tags and text size doens't match" << std::endl;

    }

    /**** 
     * printTag() -  printing only the tags
     * [option p]
     * **/
    void GNSSEN002::printTag() {

        for (int j = 0; j < Tag.size(); ++j) {
            std::cout << Tag[j].tagName << std::endl;
        }
    }

    /**** 
     * printTagInfo() - printing tag data for given tag
     * [option l]
     * **/
    void GNSSEN002::printTagInfo(std::string inputTagName) {
        
        bool found = false;
        //Looping through the stored tags searching for the tag input 
        for (int j = 0; j < Tag.size(); ++j) {
            if (Tag[j].tagName == inputTagName) {
                std::cout << "No. of Tag Pairs: " << Tag[j].noTagPairs << std::endl;
                std::cout << "Tag Text: " << Tag[j].tagText << std::endl;
                found = true;
                break;
            }
            // if (found == true)
            //     break;
        }

        //if the tag input could not be found
        if (found == false)
            std::cout << "The tag '" << inputTagName << "' could not be found." << std::endl;
    }

    /**** 
     * writeTagInfoToFile() -  writing tag data to a file called tag.txt
     * [option d]
     * **/
    void writeTagInfoToFile() {
        
        // for (int j = 0; j < Tag.size(); ++j) {
        //     std::cout << Tag[j].tagName << std::endl;
        // }
    }
    
//}   