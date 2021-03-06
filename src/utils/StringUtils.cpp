//
// Created by chiplua on 2021/7/28.
//

#include<string>
#include<iostream>
#include <vector>
#include "StringUtils.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

namespace ElisTool {
    std::string StringUtils::int2String(int line) { //整数类型文件行号 ->转换为string类型
        std::ostringstream oss;
        oss << line;
        return oss.str();
    }

    static int string2Int(std::string s) {
        int value = atoi(s.c_str());
        return value;
    }

    std::string StringUtils::intArray2String(int *pArray, int size) {
        std::string buf;
        buf.clear();
        for (int i = 0; i < size; i++) {
            unsigned char v = pArray[i];
            if (buf.size() > 0) {
                buf.append(",");
            }

            buf.append(ElisTool::StringUtils::int2String(pArray[i]));
        }

        return buf;
    }


    static std::string hexArray2String(unsigned char *pArray, int size) {
        std::string buf;
        buf.clear();

        for (int i = 0; i < size; i++) {
            unsigned char v = pArray[i];
            int h = v / 16;
            int low = v % 16;
            if (buf.size() > 0) {
                buf.append(",");
            }

            buf.append("0x").append(StringUtils::int2String(h)).append(StringUtils::int2String(low));
        }

        return buf;
    }

    std::string StringUtils::replaceAll2(std::string strSource) {
        const std::string &strOld = "%";
        const std::string &strNew = "#";
        int nPos = 0;
        while ((nPos = strSource.find(strOld, nPos)) != strSource.npos) {
            strSource.replace(nPos, strOld.length(), strNew);
            nPos += strNew.length();
        }

        return strSource;
    }

    std::vector<string> StringUtils::splitString(std::string str, std::string pattern) {
        std::string::size_type pos;
        std::vector<std::string> result;
        str += pattern;//扩展字符串以方便操作
        int size = str.size();

        for (int i = 0; i < size; i++) {
            pos = str.find(pattern, i);

            if (pos < size) {
                std::string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() - 1;
            }
        }

        return result;
    }

    std::string StringUtils::vec2String(std::vector<unsigned char> res) {
        string ret;

        for (int i = 0; i < res.size(); i++) {
            char str[4];
            sprintf(str, "%02X", res[i]);
            ret += str;
            ret += " ";
        }

        return ret;
    }

    bool StringUtils::isBccRight(std::vector<unsigned char> resVect, unsigned char bcc) {
        unsigned calBcc = 0;
        for (int i = 0; i < resVect.size() - 1; i++) {
            calBcc = (calBcc ^ resVect[i]);
        }

        return (calBcc == bcc) ? true : false;
    }
};

