/***
 * Created Date: 2022/02/24
 * Yelanika Gunasekara
 * GNSSEN002
 * 
 * tag.h 
 * 
 * ***/

#ifndef tag.h
#define tag.h

#include <string>
#include <vector>

namespace GNSSEN002 {

    struct TagStruct {
        std::string tagName;
        int noTagPairs;
        std::string tagText;
    };
}

#endif