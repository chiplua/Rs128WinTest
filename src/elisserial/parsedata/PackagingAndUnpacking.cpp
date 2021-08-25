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

        unsigned char destArray[destVector.size()];
        std::copy(destVector.begin(), destVector.end(), destArray);

        return toPrimitives(destArray, destVector.size());
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
        std::copy(commandOriginVect.begin(), commandOriginVect.end(), commandOriginArray);
        return convertArrayToSend(commandOriginArray, commandOriginVect.size());
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestConfigParameters(unsigned char conversationId,
                                                                              unsigned char generalConfiguration,
                                                                              unsigned char maxPassageAuthorization,
                                                                              unsigned char flapClosingTo,
                                                                              unsigned char passageAuthorizationTo,
                                                                              unsigned char sensorTo,
                                                                              unsigned char leaveAisleTo,
                                                                              unsigned char openSafetyTo,
                                                                              unsigned char reserve1,
                                                                              unsigned char reserve2,
                                                                              unsigned char reserve3,
                                                                              unsigned char reserve4) {
        unsigned char configurationCommand[13] = {COMMAND_PARAMETER_CONFIG,
                                                conversationId,
                                                generalConfiguration,
                                                maxPassageAuthorization,
                                                flapClosingTo,
                                                passageAuthorizationTo,
                                                sensorTo,
                                                leaveAisleTo,
                                                openSafetyTo,
                                                reserve1,
                                                reserve2,
                                                reserve3,
                                                reserve4};


        return packageCommand(configurationCommand, 13);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestSetGateMode(unsigned char conversationId, unsigned char gateMode) {
        unsigned char setGateModeCommand[3] = {COMMAND_GATE_MODE, conversationId, gateMode};

        return packageCommand(setGateModeCommand, 3);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestSetAisleMode(unsigned char conversationId, unsigned char aisleMode) {
        unsigned char setAisleModeCommand[3] = {COMMAND_AISLE_MODE, conversationId, aisleMode};

        return packageCommand(setAisleModeCommand, 3);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestPassageAuthorization(unsigned char conversationId, unsigned char direction) {
        unsigned char passageAuthorizationCommand[3] = {COMMAND_PASSAGE_AUTHORIZATION, conversationId, direction};

        return packageCommand(passageAuthorizationCommand, 3);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestTestModule(unsigned char conversationId, unsigned char testMode, unsigned char testData) {//protocal 3.4.允许通行
        unsigned char testModuleCommand[4] = {COMMAND_TEST_MODULE, conversationId, testMode, testData};

        return packageCommand(testModuleCommand, 4);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestTopIndicatorLight(unsigned char conversationId,
                                                                               unsigned char property,
                                                                               unsigned char duration,
                                                                               unsigned char flashPeriod) {
        unsigned char topIndicatorLightCommand[5] = {COMMAND_TOP_INDICATOR_LIGHT, conversationId, property, duration, flashPeriod};

        return packageCommand(topIndicatorLightCommand, 5);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestEmergency(unsigned char conversionId, unsigned char emergency) {
        unsigned char emergencyCommand[] = {COMMAND_EMERGENCY, conversionId, emergency};

        return packageCommand(emergencyCommand, 3);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestVersion(unsigned char conversationId) {
        unsigned char versionCommand[2] = {COMMAND_VERSION, conversationId};

        return packageCommand(versionCommand, 2);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestStatus(unsigned char conversationId) {
        unsigned char statusCommand[2] = {COMMAND_STATUS, conversationId};

        return packageCommand(statusCommand, 2);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestClearPasssageCount(unsigned char conversationId, unsigned char data) {
        unsigned char clearPassageCountCommand[3] = {COMMAND_CLEAR_PASSSAGE_COUNT, conversationId, data};

        return packageCommand(clearPassageCountCommand, 3);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestSetGedMode(unsigned char conversationId, unsigned char mode) {
        unsigned char setGedModeCommand[3] = {COMMAND_GED_MODE, conversationId, mode};

        return packageCommand(setGedModeCommand, 3);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestTestSensor(unsigned char conversationId, unsigned char action, unsigned char testData) {
        unsigned char sensorsTestCommand[5] = {COMMAND_TEST_MODULE, conversationId, 0x02, testData};

        return packageCommand(sensorsTestCommand, 4);
    }

    std::vector<unsigned char> PackagingAndUnpacking::requestStopCurrentTest(unsigned char conversationId, unsigned char testData) {
        unsigned char cancelCurrentTestCommand[4] = {COMMAND_TEST_MODULE, conversationId, 0x00, testData};

        return packageCommand(cancelCurrentTestCommand, 4);
    }
}