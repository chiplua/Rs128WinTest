//
// Created by chiplua on 2021/8/17.
//

#include <qDebug>
#include <qserialport.h>
#include "SerialPort.h"

namespace ElisSerial {
    SerialPort::SerialPort() {
        this->setBaudRate(BaudRate::Baud2400, QSerialPort::AllDirections);
        this->setDataBits(QSerialPort::Data8);
        this->setFlowControl(QSerialPort::NoFlowControl);
        this->setStopBits(QSerialPort::OneStop);
        this->setParity(QSerialPort::NoParity);
    }

    bool SerialPort::openPort(QString port) {
        this->setPortName(port);
        this->close();

        if (this->open(QIODevice::ReadWrite)) {
            connect(this, SIGNAL(readyRead()), this, SLOT(slotDataRec()));
            return true;
        } else {
            return false;
        }
    }

    void SerialPort::slotDataRec() {
        //receiveDataWithBrace();
    }

    void SerialPort::writeMsg(QString msg) {
        this->write(msg.toLatin1());
    }

    void SerialPort::writeByteArray(QByteArray byteArray) {
        this->write(byteArray);
    }

    /*
    void SerialPort::receiveDataWithBrace() {
        QByteArray bufferData = this->readAll();
        //qDebug()<<temp;
        if ((!bufferData.contains("{")) & (pasteData.isNull())) {
            return;
        }

        //第一种：有头无尾，先清空原有内容，再附加
        if ((bufferData.contains("{")) & (!bufferData.contains("}"))) {
            pasteData.clear();
            pasteData.append(bufferData);
        }

        //第二种：无头无尾且变量已有内容，数据中段部分，继续附加即可
        if ((!bufferData.contains("{")) & (!bufferData.contains("}")) & (!pasteData.isNull())) {
            pasteData.append(bufferData);
        }

        //第三种：无头有尾且变量已有内容，已完整读取，附加后输出数据，并清空变量
        if ((!bufferData.contains("{")) & (bufferData.contains("}")) & (!pasteData.isNull())) {
            pasteData.append(bufferData);
            readData = pasteData;
            pasteData.clear();
        }

        //第四种：有头有尾（一段完整的内容），先清空原有内容，再附加，然后输出，最后清空变量
        if ((bufferData.contains("{")) & (bufferData.contains("}"))) {
            pasteData.clear();
            pasteData.append(bufferData);
            readData = pasteData;
            pasteData.clear();
        }
        //qDebug() << "" << readData.replace("{", "").replace("}", "");
        if (!readData.isEmpty()) {
            qDebug() << "readData = " << readData;
            readData.clear();
        }
    } */
}