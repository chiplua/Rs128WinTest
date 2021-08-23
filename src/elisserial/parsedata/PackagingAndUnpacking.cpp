//
// Created by chiplua on 2021/8/20.
//
/*
* 1.先取得命令数据DATA
* 2.取得DATA的长度LEN
* 3.LEN和DATA异或得到BCC
* 4.添加第一个字节0x02
* 5.添加最后一个字节0x03
* 6.转义
* 7.发送出去
*
* * 解包步骤：
* 1.去掉第一个字节
* 2.去掉最后一个字节
* 3.转义
* 4.得到LEN、DATA、BCC
* 5.校验BCC，判断LEN
* 6.得到DATA
*
* */



#include <QDebug>
#include "PackagingAndUnpacking.h"

namespace ElisSerial {
    std::vector<unsigned char> PackagingAndUnpacking::toPrimitives(unsigned char oBytes[], int arraySize) {
        std::vector<unsigned char> bytes;

        bytes.push_back(0x02);

        for(int i = 0; i < arraySize; i++) {
            bytes.push_back(oBytes[i]);
        }

        bytes.push_back(0x03);

        return bytes;
    }
}