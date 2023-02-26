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
#include <fstream>

    /***
     * * ExtractTagsandText() - Reading and processes input tag file
     *  [option r] 
     * 
     * **/
    void GNSSEN002::ExtractTagsandText(std::vector<std::string> tagInfo) {
        
        std::vector<std::string> tags;
        std::vector<std::string> text; 
        int tagIndex = -1;
        std::vector<int> no_tagPairs;
        std::vector<std::string> nestedTags;
        bool flag_openTag;
        bool tagExists;

        while (Tag.size() > 0) {        //clear Tag info of the previous file
                Tag.pop_back();
        }

        for (int lineNo = 0; lineNo < tagInfo.size(); ++lineNo) {      //going through each line of the textfile

            std::string TagInfo_currentLine = tagInfo[lineNo];      //current line of file

            bool found_ClosingTag = false; //check for the end tag 

            std::size_t TagPos_Start = -1;

            if ((TagInfo_currentLine.length()) == 0)       //line is empty
                //ends this iteration and goes to the next line
                continue;
            else {              //else capture the data in the line

                char action = 'a';  //the action that will take place in the below switch statement
                
                bool notEmpty = true;
                bool tagInText = false;

                //in case statement:
                // case 'a' - Assignment to tag 'b' or 'c' based on line infomation
                // case 'b' - A tag has been found
                // case 'c' - Tag info has been found
                
                //while loop going through each line              
                while(notEmpty) {
                    switch(action) {
                        case 'a' : {    //option assign

                            if (TagInfo_currentLine.length() == 0)  {       //if line is empty move onto next line
                                notEmpty = false;
                                break;
                            }
                            else {
                                TagPos_Start = TagInfo_currentLine.find("<");                                

                                //if there is a tag in the current line
                                if (TagPos_Start != std::string::npos) {

                                    if (TagPos_Start == 0) {    //if tag is in the first position
                                        action = 'b';   //option tag
                                        break;
                                    }
                                    else {          // else text is before tag
                                        tagInText = true;
                                        action = 'c';   //option text
                                        break;
                                    }
                                }
                                else {  //there is no tag in the line, just text
                                    action ='c';    //option text
                                    break;
                                }
                            }
                            break;
                        }
                        case 'b' : {    //option tag

                            //if there is a tag in the current line
                            if (TagPos_Start != std::string::npos) {
            
                                std::size_t TagPos_End = TagInfo_currentLine.find(">");   //finding the end of the tag 
                                std::string tag = TagInfo_currentLine.substr(TagPos_Start,TagPos_End-TagPos_Start+1); 

                                
                                bool inner_bracket = true;
                                std::size_t test_tag_open = -1;
                                std::string test_tag = tag.substr(1,tag.size());

                                while (inner_bracket) {         //testing whether a tag has any inner <

                                    test_tag_open = test_tag.find("<");
                                    if (test_tag_open != std::string::npos) {
                                        test_tag = test_tag.substr(test_tag_open+1,test_tag.size());
                                        tagInText = true;
                                        TagPos_Start = test_tag_open;
                                        //if inner < exists, add pre-text to the open tag info
                                        action = 'c';           //assign = text
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
                                    nestedTags.pop_back();
                                    flag_openTag = false;
                                }
                                else {            //opening tag
                                    nestedTags.push_back(tag);
                                    flag_openTag = true;
                                    for (int check_SameTag = 0; check_SameTag < tags.size(); ++check_SameTag) {
                                        if (tag == tags[check_SameTag]) {       //check whether an opening tab already exists
                                            
                                            tagIndex = check_SameTag;           
                                            no_tagPairs[tagIndex]++;
                                            break;
                                        }
                                        else{
                                            tagIndex = - 1;     //a new tag has been found
                                        }
                                    }
                                    if (tagIndex == -1) {       
                                        tags.push_back(tag);        //adding new tag to vector of tags
                                        no_tagPairs.push_back(1);
                                        tagExists = false;
                                    }
                                    else    
                                        tagExists = true;       //indicating the opening tag already exists in the tag vector
                                }
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_End+1); 
                            }
                            action = 'a';    //option = assign
                            break;
                        }
                        case 'c' : {    //option = text
                            
                            std::string tagInfo = "";

                            if (tagInText == true) {     //there is a tag after the text
                                tagInfo = TagInfo_currentLine.substr(0,TagPos_Start);
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_Start);
                            }
                            else { //no tag in text
                                tagInfo = TagInfo_currentLine;
                                TagInfo_currentLine = TagInfo_currentLine.substr(tagInfo.size());
                            }
                            
                            bool tabFound = true;
                            while (tabFound) {          //checking whether there is tab spaces before text appears
                                if (tagInfo[0] == '\t') {
                                    tagInfo = tagInfo.substr(1, tagInfo.size());
                                }
                                else
                                    tabFound = false;
                            }
                           
                            if (tagIndex == -1) {   
                                //Adding new tag infomation
                                if ((tags.size() -text.size()) > 1)
                                    text.push_back("");
                                text.push_back(tagInfo);
                                tagIndex = tags.size() -1; 
                            }
                            else if ((flag_openTag == true) and (tagExists == true)) {
                                //Adding infomation to an exisiting tag with :
                                text[tagIndex] += " : " + tagInfo;
                            }
                            else if (flag_openTag == true) {
                                //Adding additional infomation to an open tag
                                text[tagIndex] += tagInfo;
                            }
                            else if (flag_openTag == false) {
                                //Adding additional infomation to a nested open tag
                                std::string nestedTag = nestedTags[nestedTags.size() - 1];
                                for (int nested = 0; nested < tags.size(); ++nested) {
                                    if (nestedTag == tags[nested]) { 
                                        tagIndex = nested;
                                        break;
                                    }
                                }
                                text[tagIndex] += tagInfo;
                            }
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

        //Allocating Tag, no. of tag pairs and tag text to the TagStruct variables
        if (tags.size() == text.size() and (tags.size() == no_tagPairs.size())) { 
            for (int i = 0; i < tags.size(); ++i) {
                //std::cout << "Tag: " << tags[i] << " pairs: " << no_tagPairs[i] << " Text: " << text[i] << std::endl;
                Tag.push_back({tags[i], no_tagPairs[i], text[i]});
            }
        }
        else     //if there is an error and the size of the tag vector, no. of pairs vector and tag text vector do not match
            std::cout << "Error: tags and text size doens't match" << std::endl;
    }

    /**** 
     * printTag() -  printing only the tags
     * [option p]
     * **/
    void GNSSEN002::printTag() {
        
        //looping through and printing out tag names only
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
        }
        
        //if the tag input could not be found
        if (found == false)
            std::cout << "The tag '" << inputTagName << "' could not be found." << std::endl;
    }

    /**** 
     * writeTagInfoToFile() -  writing tag data to a file called tag.txt
     * [option d]
     * **/
    void GNSSEN002::writeTagInfoToFile() {

        std::ofstream out("tag.txt");
        
        //Looping through tag data and writng it to a file
        for (int j = 0; j < Tag.size(); ++j) {
            out << "\"" << Tag[j].tagName << "\"," << Tag[j].noTagPairs << ",\"" << Tag[j].tagText << "\"" << std::endl;
        }

        out.close();
    } 