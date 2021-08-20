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
    char* PackagingAndUnpacking::toPrimitives(char oBytes[], int arraySize) {
        char bytes[arraySize + 2];

        bytes[0] = 0x02;
        bytes[arraySize + 1] = 0x03;

        for(int i = 0; i < arraySize; i++) {
            bytes[i + 1] = oBytes[i];
        }

        return bytes;
    }
}