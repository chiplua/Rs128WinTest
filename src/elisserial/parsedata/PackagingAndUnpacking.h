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
    };
}
#endif //ELISRS128WINTEST_PACKAGINGANDUNPACKING_H
/*
        static char[] requestClientRadarStartScan(int conversationId, CommandModel commandModel);
        static char[] requestClientRadarStopScan(short conversationId, CommandModel commandModel);
        static char[] requestClientStartDesinfection(short conversationId, int minutes, CommandModel commandModel);
        static char[] requestClientStopDesinfection(short conversationId, int minutes, CommandModel commandModel);
        static char[] requestClientVersions(short conversationId, CommandModel commandModel);
        static char[] requestClientStatus(short conversationId, CommandModel commandModel);
        static char[] requestClientStartPilotLed(short conversationId, CommandModel commandModel);
        static char[] requestClientStopPilotLed(short conversationId, CommandModel commandModel);
        static char[] responseClientSomeBodyIn(short conversationId, byte resultCode, CommandModel commandModel);
        static char[] requestClientUpdateFirmware(short conversationId, CommandModel commandModel, byte board, byte number);
        static char[] requestClientSendFirmwareLength(short conversationId, CommandModel commandModel, byte board, byte number, int length);
        static char[] requestClientSendFirmwareData(short conversationId, CommandModel commandModel, byte board, byte number, byte[] data);
        static char[] requestClientSendFirmwareOver(short conversationId, CommandModel commandModel, byte board, byte number);
        static char[] requestClientBootloader2Mainboard(short conversationId, CommandModel commandModel, byte board, byte number);
        static char[] packageCommand(byte[] commandDataArray, CommandModel commandModel);
        static char[] convertArrayToSend(byte[] originArray, CommandModel commandModel);
        static char[] convertReceivedArray(byte[] originArray);
*/
