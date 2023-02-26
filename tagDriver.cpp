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
    bool fileExists = false;

    if (argc == 1) {        //No parameters should be entered

        for(;;) {         //Infinite loop
            switch (option) {                 //case statement holding all the different available options 
        
                case 'm' : {        // the Menu
                    std::cout << "r: Read and process tag file" << std::endl;
                    std::cout << "p: Print all tags" << std::endl;
                    std::cout << "d: Write tags and data to a file called tag.txt" << std::endl;
                    std::cout << "l: Print tag data for given tag" << std::endl;
                    std::cout << "q: Quit" << std::endl;

                    std::cout << "choose: ";
                    std::cin >> option;     //User input of option

                    if ((option != 'r') or (option != 'p') or (option != 'd') or (option != 'l') or (option != 'q'))
                        break;
                    else {
                        std::cout << "The option you have choosen does not exist, please try again." << std::endl;
                        option = 'm';
                    }
                    
                    break;
                }
                case 'r' : {            //Getting input file 

                    std::cout << " " << std::endl;
                    std::cout << "Enter your file name: " << std::endl;

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
                        fileExists = true;
                        std::cout << "Your file " << filename << " has been loaded successfully." << std::endl;
                    }
                    else    //If there is no infomation in the textfile
                        std::cout << "Error: There is no data in the file provided. " << filename << std::endl;

                    std::cout << " " << std::endl;
                        
                    option = 'm';
                    break;
                }
                case 'p' : {        // just printing the tags

                    std::cout << " " << std::endl;
                
                    if (fileExists)
                        GNSSEN002::printTag();
                    else  {
                        std::cout << "File does not exist." << std::endl;
                        std::cout << "Please use the option 'r' to input a file." << std::endl;
                    }

                    std::cout << " " << std::endl;

                    option = 'm';
                    break;
                }
                case 'd' : {        //writing tags and data to file(tag.txt)

                    std::cout << " " << std::endl;
                    
                    if (fileExists) {
                        GNSSEN002::writeTagInfoToFile();
                        std::cout << "The tag infomation has been successfully written to tag.txt." << std::endl;
                    }
                    else  {
                        std::cout << "File does not exist." << std::endl;
                        std::cout << "Please use the option 'r' to input a file." << std::endl;
                    }

                    std::cout << " " << std::endl;

                    option = 'm';
                    break;
                }
                case 'l' : {        //printing tag data for given tag
                    std::cout << " " << std::endl;

                    if (fileExists) {
                        std::string tagInput = "";
                        std::cout << "Please enter a tag name: " << std::endl;
                        std::cin >> tagInput;
                        GNSSEN002::printTagInfo(tagInput);
                    }
                    else  {
                        std::cout << "File does not exist." << std::endl;
                        std::cout << "Please use the option 'r' to input a file." << std::endl;
                    }

                    std::cout << " " << std::endl;

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