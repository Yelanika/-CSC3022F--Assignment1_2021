/***
 * Created Date: 2022/02/24
 * Yelanika Gunasekara
 * GNSSEN002
 * 
 * tag.h 
 * 
 * ***/

#ifndef tag_h
#define tag_h

#include <string>
#include <vector>

namespace GNSSEN002 {

    struct TagStruct {
        std::string tagName;
        int noTagPairs;
        std::string tagText;
    };

    std::vector<TagStruct> Tag;
    void ExtractTagsandText(std::vector<std::string> tagInfo);
    void printTag();
    void printTagInfo(std::string inputTagName);    

}

#endif