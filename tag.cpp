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

        for (int i = 0; i < tagInfo.size(); ++i) {      //going through each line of the textfile

            std::string TagInfo_currentLine = tagInfo[i];      

            bool found_endTag = false; //to check if the end tag is found first

            //variables to help identify if the line has any values or is empty 
            //std::string copy_TagInfo_currentLine = TagInfo_currentLine;       
            //int spaces = 0;

            //if empty line - space would be 0
            //thus, would not go through this loop
            //tabbed space counts as text not as a space, thus spaces = 0
            // for (int j = 0; j < copy_TagInfo_currentLine.length(); ++j) {
            //     if (copy_TagInfo_currentLine.at(j) == ' ')
            //         spaces++;

            //     //what happens when spaces end and somnething is found???
            // }       
            //std::cout << "current line " << copy_TagInfo_currentLine.length() << "      " << "spaces " << spaces << std::endl;
            //if the no. of spaces in the line = length of the line-1, then iterate again and go to next line
            if ((TagInfo_currentLine.length()) == 0)       //line is empty
                //ends this iteration and goes to the next iteration
                continue;
            else {              //else capture the data in the line

                //Getting the tag
                std::size_t StartTagPos = TagInfo_currentLine.find("<");

                //if there is a tag in the current line
                if (StartTagPos!=std::string::npos) {
                    std::size_t EndtagPos = TagInfo_currentLine.find(">");   //finding the end of the tag 
                    std::string tag = TagInfo_currentLine.substr(StartTagPos,EndtagPos-StartTagPos+1);  //dont understand this????

                    std::size_t EndTagPos = tag.find("/");

                    if (EndTagPos!=std::string::npos)  //if an endtag is found
                        found_endTag = true;
                    else {
                        tags.push_back(tag);

                        //current line without the tag
                        TagInfo_currentLine = TagInfo_currentLine.substr(EndtagPos+1);

                        //Check for text once the tag is removed 
                        if (TagInfo_currentLine.length() == 0)
                            found_endTag = true;
                    }                    
                }

                //if the end tag is found first - then skip this section of pushing back text
                if (found_endTag == false) {    
                    //Getting the text - looking for end tag
                    std::size_t StextPos = TagInfo_currentLine.find("<");

                    //if end tag is found & we are getting the text
                    if (StextPos!=std::string::npos) {
                        std::size_t EtextPos = TagInfo_currentLine.find(">");
                        std::string tText = TagInfo_currentLine.substr(0,StextPos);
                        text.push_back(tText);
                    }
                    else    //else there must only be string left in the current line 
                        text.push_back(TagInfo_currentLine);
                }
            }        
        }        
        Tag.push_back({tags[0], 1, text[0]});

        if (tags.size() > 1) {
            for (int i = 1; i < tags.size(); ++i) {
                
                bool found = false;
                int k_tag;

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
                    Tag[k_tag-1].noTagPairs++;
                    Tag[k_tag-1].tagText += " : " + text[i];
                }
                else                //if a new tag name is found
                    Tag.push_back({tags[i], 1, text[i]});  

            }

        }
        
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