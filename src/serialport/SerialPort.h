//
// Created by chiplua on 2021/8/17.
//

#ifndef ELISRS128WINTEST_SERIALPORT_H
#define ELISRS128WINTEST_SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>

namespace ElisSerial {
    class SerialPort : public QSerialPort {
        Q_OBJECT
    public:
        SerialPort();

        bool openPort(QString);

        void writeMsg(QString);

        void writeByteArray(QByteArray byteArray);

    private
        slots:
                void slotDataRec();

    private:
        void receiveDataWithBrace();
    };
}
#endif //ELISRS128WINTEST_SERIALPORT_H
