//
// Created by chiplua on 2021/7/28.
//

#ifndef ELISSGPGATECPP_STRINGUTILS_H
#define ELISSGPGATECPP_STRINGUTILS_H

#include <sstream>

namespace ElisTool {
    class StringUtils {
    public:
        static std::string int2String(int line);
        static std::string replaceAll2(std::string strSource);
        static std::vector<std::string> splitString(std::string str, std::string pattern);
        static std::string intArray2String(int *pArray, int size);
        static void hexToAscii(void* destBuf, void* srcBuf, int srcLen);
    };
}
#endif //ELISSGPGATECPP_STRINGUTILS_H
