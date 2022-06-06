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
#include <fstream>
#include <sstream>
#include <cstdlib>

//namespace GNSSEN002 {}
int main (int argc, char* argv[]) {
    std::vector<GNSSEN002::TagStruct> Tag;
    
    // std::string filename = "simple.txt";

    // if (argc == 1)
    //     filename = "simple.txt";
    // else
    //     filename = argv[1];

    // std::ifstream in(filename);
  
    // if(!in) {
    //     std::cout << "Couldn't open file" << filename << std::endl;
    //     return 1;
    // }

    // std::string line;
    // while (std::getline(in, line)) {
    //     tagInfo.push_back(line);
    // }

    // in.close();

    // if (tagInfo.size() > 0) {
    //     GNSSEN002::ExtractTagsandText(tagInfo);
    // }
    // else    
    //     std::cout << "There is no data in the file provided: " << filename << std::endl;
    // return 0;

    
    char option = 'm';      // m - Menu
    std::string filename = "";        

    if (argc == 1) {        //No parameters should be entered

        for(;;) {         //Infinite loop
            switch (option) {                 //case statement holding all the different available options 
        
                case 'm' : {        // the Menu
                    std::cout << "r: Read and process tag file" << std::endl;
                    std::cout << "p: Print all tags" << std::endl;
                    std::cout << "d: Write tags and data to a file called tag.txt" << std::endl;
                    std::cout << "r: Print tag for given tag" << std::endl;
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
                        GNSSEN002::ExtractTagsandText(tagInfo);
                    }
                    else    //If there is no infomation in the textfile
                        std::cout << "Error: There is no data in the file provided: " << filename << std::endl;
                        
                    option = 'm';
                    break;
                }
                case 'p' : {        // just printing the tags
            
                    option = 'm';
                    break;
                }
                case 'd' : {        //writing tags and data to file(tag.txt)

                    
                    option = 'm';
                    break;
                }
                case 'l' : {

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
}