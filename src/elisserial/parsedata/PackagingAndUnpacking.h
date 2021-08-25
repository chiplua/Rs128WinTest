//
// Created by chiplua on 2021/8/20.
//

#ifndef ELISRS128WINTEST_PACKAGINGANDUNPACKING_H
#define ELISRS128WINTEST_PACKAGINGANDUNPACKING_H

namespace ElisSerial {
    class PackagingAndUnpacking {
    private:
        static const int BEGIN_COMMAND_BYTE = 0x02;
        static const int END_COMMAND_BYTE = 0x03;
    public:
        static std::vector<unsigned char> toPrimitives(unsigned char oBytes[], int arraySize);
        static std::vector<unsigned char> convertReceivedArray(unsigned char originArray[], int arraySize);
        static std::vector<unsigned char> convertArrayToSend(unsigned char originArray[], int arraySize);
        static std::vector<unsigned char> packageCommand(unsigned char commandDataArray[], int arraySize);
        static std::vector<unsigned char> requestVersion(unsigned char conversationId);
        static std::vector<unsigned char> requestConfigParameters(unsigned char conversationId,
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
                                                                  unsigned char reserve4);
        static std::vector<unsigned char> requestSetGateMode(unsigned char conversationId, unsigned char gateMode);
        static std::vector<unsigned char> requestSetAisleMode(unsigned char conversationId, unsigned char aisleMode);
        static std::vector<unsigned char> requestStatus(unsigned char conversationId);
        static std::vector<unsigned char> requestTestModule(unsigned char conversationId, unsigned char testMode, unsigned char testData);
        static std::vector<unsigned char> requestTopIndicatorLight(unsigned char conversationId,
                                                                   unsigned char property,
                                                                   unsigned char duration,
                                                                   unsigned char flashPeriod);
        static std::vector<unsigned char> requestEmergency(unsigned char conversionId, unsigned char emergency);
        static std::vector<unsigned char> requestClearPasssageCount(unsigned char conversationId, unsigned char data);
        static std::vector<unsigned char> requestSetGedMode(unsigned char conversationId, unsigned char mode);
        static std::vector<unsigned char> requestTestSensor(unsigned char conversationId, unsigned char action, unsigned char testData);
        static std::vector<unsigned char> requestStopCurrentTest(unsigned char conversationId, unsigned char testData);
        static std::vector<unsigned char> requestPassageAuthorization(unsigned char conversationId, unsigned char direction);
    };
}
#endif //ELISRS128WINTEST_PACKAGINGANDUNPACKING_H
