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

    std::vector<unsigned char> PackagingAndUnpacking::convertReceivedArray(unsigned char originArray[], int arraySize) {
        std::vector<unsigned char> recvVect;

        if (originArray[0] != PackagingAndUnpacking::BEGIN_COMMAND_BYTE ||
            originArray[arraySize - 1] != PackagingAndUnpacking::END_COMMAND_BYTE) {
            return {};
        }

        for (int i = 1; i < arraySize - 1; i++) {
            if (originArray[i] == 0x10 && originArray[i + 1] == 0x02) {
                recvVect.push_back(originArray[i + 1]);
                i++;
            } else if (originArray[i] == 0x10 && originArray[i + 1] == 0x03 && (i + 1) != (arraySize - 1)) {
                recvVect.push_back(originArray[i + 1]);
                i++;
            } else if (originArray[i] == 0x10 && originArray[i + 1] == 0x10) {
                recvVect.push_back(originArray[i + 1]);
                i++;
            } else {
                recvVect.push_back(originArray[i]);
            }
        }

        unsigned char destArray[recvVect.size()];
        std::vector<unsigned char> destVector = toPrimitives(std::copy(recvVect.begin(), recvVect.end(), destArray), recvVect.size());
        unsigned char bcc = destVector.size();

        for (int i = 1; i < destVector.size(); i++) {
            bcc = (bcc ^ destVector[i]);
        }

        return destVector;
    }

    std::vector<unsigned char> PackagingAndUnpacking::convertArrayToSend(unsigned char originArray[], int arraySize) {
        std::vector<unsigned char> destVector;

        for (int i = 0; i < arraySize; i++) {
            if (originArray[i] == 0x02) {
                destVector.push_back(0x10);
                destVector.push_back(0x02);
            } else if (originArray[i] == 0x03) {
                destVector.push_back(0x10);
                destVector.push_back(0x03);
            } else if (originArray[i] == 0x10) {
                destVector.push_back(0x10);
                destVector.push_back(0x10);
            } else {
                destVector.push_back(originArray[i]);
            }
        }

        return destVector;
    }

    std::vector<unsigned char> PackagingAndUnpacking::packageCommand(unsigned char commandDataArray[], int arraySize) {
        std::vector<unsigned char> commandOriginVect;
        commandOriginVect.push_back(arraySize);

        unsigned char bcc = arraySize;
        for (int i = 0; i < arraySize; i++) {
            commandOriginVect.push_back(commandDataArray[i]);
            bcc = bcc ^ commandDataArray[i];
        }

        commandOriginVect.push_back(bcc);

        unsigned char commandOriginArray[commandOriginVect.size()];
        return convertArrayToSend(std::copy(commandOriginVect.begin(), commandOriginVect.end(), commandOriginArray), commandOriginVect.size());
    }


}