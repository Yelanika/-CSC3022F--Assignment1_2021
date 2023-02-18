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

        for (int lineNo = 0; lineNo < tagInfo.size(); ++lineNo) {      //going through each line of the textfile

            std::string TagInfo_currentLine = tagInfo[lineNo];      

            bool found_ClosingTag = false; //to check if the end tag is found first

            if ((TagInfo_currentLine.length()) == 0)       //line is empty
                //ends this iteration and goes to the next iteration
                continue;
            else {              //else capture the data in the line

                char action = 'b';  //the action that will take place in the below switch statement
                int no_nestedTag = 0;
                bool notEmpty = true;
                bool tagInText = false;

                
                //for loop going through each line
                //nestedTag_no                
                while(notEmpty) {
                    switch(action) {
                        case 'a' : {    //option = assign

                            if (TagInfo_currentLine.length() == 0) {       //if line is empty
                                notEmpty = false;
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

                            //Checking for the beginning of a tag
                            std::size_t TagPos_Start = TagInfo_currentLine.find("<");

                            //if there is a tag in the current line
                            if (TagPos_Start != std::string::npos) {
                            //     action = 'b';//option:tag
                            // else
                            //     action = 'c';//option text
                                std::size_t TagPos_End = TagInfo_currentLine.find(">");   //finding the end of the tag 
                                std::string tag = TagInfo_currentLine.substr(TagPos_Start,TagPos_End-TagPos_Start+1); 

                                std::size_t find_ClosingTag = tag.find("/");    //check if tag is a closing tag
                                if (find_ClosingTag != std::string::npos)
                                    no_nestedTag--;
                                else {            //opening tag
                                    tags.push_back(tag);
                                    no_nestedTag++;
                                    TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_End+1); 
                                }
                            }
                            action = 'a';    //option = assign
                            break;
                        }
                        case 'c' : {    //option = text

                            std::string tagInfo = " ";

                            if (tagInText = true) {     //there is a tag after the text
                                std::size_t TagPos_Start = TagInfo_currentLine.find("<");
                                tagInfo = TagInfo_currentLine.substr(0,TagPos_Start);
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_Start);
                            }
                            else { //no tag in text
                                tagInfo = TagInfo_currentLine;
                                TagInfo_currentLine = TagInfo_currentLine.substr(0);
                            }

                            if (no_nestedTag == 1)
                                text.push_back(tagInfo);
                            else 
                                text[tags.size() - no_nestedTag - 1] = tagInfo;
                    
                            tagInText = false;
                            action = 'a';   //option = assign
                            break;
                        }
                        // case 'd' : {    //nothing left in the line
                        //     break;
                        // }
                        default:
                            break;
                    }
                }
            }
        }
    }
                //     std::size_t find_ClosingTag = tag.find("/");        //check if the tag is an closing tag

                //     if (find_ClosingTag != std::string::npos)  //if an closing tag is found
                //         found_ClosingTag = true;
                //         //option closingTag
                // //case : closingTag
                //     else {      //else it would be an opening tag
                //         tags.push_back(tag);

                //         //current line without the tag
                //         TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_End+1);
                //         std::cout << "line " << lineNo << "  tag: " << tag << "  current line: " << TagInfo_currentLine << std::endl;
                //         //Check for text once the tag is removed 
                //         if (TagInfo_currentLine.length() == 0)
                //             continue;
                //             //found_ClosingTag = true; 
                //     }                    
                // }

                //if there is no tag - it would be text
                //else
                //you would store text until the next < or until TagInfo_currentLine.length() == 0


                //if the end tag is found first - then skip this section of pushing back text
                // if (found_ClosingTag == false) {    
                //     //Getting the text - looking for end tag
                //     std::size_t StextPos = TagInfo_currentLine.find("<");

                //     //if end tag is found & we are getting the text
                //     if (StextPos!=std::string::npos) {
                //         std::size_t EtextPos = TagInfo_currentLine.find(">");
                //         std::string tText = TagInfo_currentLine.substr(0,StextPos);
                //         text.push_back(tText);
                //     }
                //     else    //else there must only be string left in the current line 
                //         text.push_back(TagInfo_currentLine);
                // }
           // }        
       // }        
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