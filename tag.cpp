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

        //int tags_size = tags.size();
        //int texts_size = text.size();
        //if (tags_size == texts_size) {

            //int counter = 0;
            //while ((tags_size != 0) and (texts_size != 0)) {
                

            //}
        //}
        //else 
        //std::cout << "Error: The no. of tags and assciated texts are unequal" << std::endl;

        for (int lineNo = 0; lineNo < tagInfo.size(); ++lineNo) {      //going through each line of the textfile

            std::string TagInfo_currentLine = tagInfo[lineNo];    
             
            
            //Testing
            //if (lineNo == 6)
              //  break;
            bool found_ClosingTag = false; //to check if the end tag is found first

            if ((TagInfo_currentLine.length()) == 0)       //line is empty
                //ends this iteration and goes to the next iteration
                continue;
            else {              //else capture the data in the line

                char action = 'b';  //the action that will take place in the below switch statement
                
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
                                break;
                                //continue;
                            }
                            else {
                                //Checking for the beginning of a tag
                                std::size_t TagPos_Start = TagInfo_currentLine.find("<");
                            
                                //if there is a tag in the current line
                                if (TagPos_Start != std::string::npos) {
                                    if (TagPos_Start == 0) {    //if tag is in the first position
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
                                    action ='c';
                                    break;
                                }
                            }
                            break;
                        }
                        case 'b' : {    //option = tag
                            std::cout << lineNo << " Tag: " << TagInfo_currentLine << std::endl;
                            //Checking for the beginning of a tag
                            std::size_t TagPos_Start = TagInfo_currentLine.find("<");

                            //if there is a tag in the current line
                            if (TagPos_Start != std::string::npos) {
                            //     action = 'b';//option:tag
                            // else
                            //     action = 'c';//option text
                                std::size_t TagPos_End = TagInfo_currentLine.find(">");   //finding the end of the tag 
                                std::string tag = TagInfo_currentLine.substr(TagPos_Start,TagPos_End-TagPos_Start+1); 

                                //search for another < in the tag
                                //start at tag[1]
                                //for loop through tag.size()
                                //if < found -> tag[]
                                std::size_t find_ClosingTag = tag.find("/");    //check if tag is a closing tag
                                if (find_ClosingTag != std::string::npos)
                                    no_nestedTag--;
                                else {            //opening tag
                                    tags.push_back(tag);
                                    no_nestedTag++;
                                }
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_End+1); 
                                std::cout << lineNo << " Tag: no_nestedTag: " << no_nestedTag << std::endl;
                            }
                            action = 'a';    //option = assign
                            break;
                        }
                        case 'c' : {    //option = text
                            std::cout << lineNo << " Text: " << TagInfo_currentLine << std::endl;
                            std::string tagInfo = " ";

                            if (tagInText == true) {     //there is a tag after the text
                                std::size_t TagPos_Start = TagInfo_currentLine.find("<");
                                tagInfo = TagInfo_currentLine.substr(0,TagPos_Start);
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_Start);
                            }
                            else { //no tag in text
                                tagInfo = TagInfo_currentLine;
                                //std::cout << "Error 1" << std::endl;
                                TagInfo_currentLine = TagInfo_currentLine.substr(tagInfo.size());
                                std::cout << "Error 2" << std::endl;
                            }

                            std::cout << lineNo << " Text: no_nestedTag: " << no_nestedTag << " info: " << TagInfo_currentLine << std::endl;
                            if (no_nestedTag == 1)
                                text.push_back(tagInfo);
                            //no_nestedTag to current_nestedTagNo
                            //prev_no_nestedTag = no_nestedTag; //at the beginneing of lineno loop
                            //if (no_nestedTag == prev_nestedTagNo)
                            //text.push_back(tagInfo);
                            //if (no_nestedTag > 1) {       //nesting of tags is taking place
                            //if (prev_nestedTagNo > current_nestTagNo)        //tag has been added to nest
                            //text.push_back(tagInfo)
                            //else if (prev_nestedTagNo < current_nestTagNo)    //tag has been removed from the nest
                            //text[tags.size() - 2] = tagInfo      //HOW DO WE FIND THE TEXT_NO -> test[text_no]?????
                            //}
                            else {
                                std::cout << "Error 3" << std::endl;
                                text[tags.size() - no_nestedTag - 1] = tagInfo;
                                std::cout << "Error 4" << std::endl;
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
    }
        
        // Tag.push_back({tags[0], 1, text[0]});

        // if (tags.size() > 1) {
        //     for (int i = 1; i < tags.size(); ++i) {     //need to change i to different variable name
                
        //         bool found = false;
        //         int k_tag;

        //         //search for the same tag
        //         for (k_tag = 1; k_tag < i+1; ++k_tag) { //k_tag = position of the tag in vector

        //             //condition: to not check same tag against each other
        //             if ((k_tag-1) != i) {
        //                 if (tags[i] == tags[k_tag-1]) {
        //                     found = true;
        //                     break;      //break out of loop
        //                 }
        //             }
        //         }
                
        //         if (found)  {       //if found is true
        //             Tag[k_tag-1].noTagPairs++;
        //             Tag[k_tag-1].tagText += " : " + text[i];
        //         }
        //         else                //if a new tag name is found
        //             Tag.push_back({tags[i], 1, text[i]});  

        //     }

        // }
        
   // }

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
            }
            if (found == true)
                break;
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