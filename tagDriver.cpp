/***
 * Created Date: 2022/02/24
 * Yelanika Gunasekara
 * GNSSEN002
 * 
 * tagDriver.cpp
 * 
 * ***/

#include "tag.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

//namespace GNSSEN002 {}
int main (int argc, char* argv[]) {
  
    char option = 'm';      // m - Menu
    std::string filename = "";   

    if (argc == 1) {        //No parameters should be entered

        for(;;) {         //Infinite loop
            switch (option) {                 //case statement holding all the different available options 
        
                case 'm' : {        // the Menu
                    std::cout << "r: Read and process tag file" << std::endl;
                    std::cout << "p: Print all tags" << std::endl;
                    std::cout << "d: Write tags and data to a file called tag.txt" << std::endl;
                    std::cout << "l: Print tag for given tag" << std::endl;
                    std::cout << "q: Quit" << std::endl;

                    std::cin >> option;     //User input of option

                    std::cout << "choose: " << option << std::endl;
                    break;
                }
                case 'r' : {            //Getting input file 

                    std::cin >> filename;       //User input of tag file

                    //BEGINNING OF READING FILE
                    std::ifstream in(filename);                    
                    if(!in) {       //if file cannot be open then error printed & goes back to menu
                        std::cout << "Error: File could not be open." << filename << std::endl;
                        option = 'm';       
                        break;       
                    }

                    std::string line;
                    std::vector<std::string> tagInfo;       //holds everyline in the textfile

                    //Getting the infomation from the textfile
                    while (std::getline(in, line)) {
                        tagInfo.push_back(line);
                    }

                    in.close();         //closing input file
                    //END OF READING FILE

                    if (tagInfo.size() > 0) {   //if there is infomation int the textfile
                        std::cout << "Tags and text" << std::endl; //for testing
                        //GNSSEN002::ExtractTagsandText(tagInfo);
                        //std::cout << Tag[0].tagName << std::endl;
                    }
                    else    //If there is no infomation in the textfile
                        std::cout << "Error: There is no data in the file provided. " << filename << std::endl;
                        
                    option = 'm';
                    break;
                }
                case 'p' : {        // just printing the tags
                
                    //GNSSEN002::printTag();
                    std::cout << "just tags" << std::endl;  //testing

                    option = 'm';
                    break;
                }
                case 'd' : {        //writing tags and data to file(tag.txt)

                    option = 'm';
                    break;
                }
                case 'l' : {        //printing tag data for given tag

                    std::string tagInput = "";
                    std::cin >> tagInput;
                    //GNSSEN002::printTagInfo(tagInput);
                    std::cout << "printing tag info" << std::endl;  //testing

                    option = 'm';
                    break;
                }
                case 'q' : {    //End the program
                    return 1;
                }
                default:
                    break;
            }
        }
    } 

    return 1;
}