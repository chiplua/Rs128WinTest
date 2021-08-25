//
// Created by chiplua on 2021/8/25.
//

#include "CustomComboBox.h"

namespace ElisView {
    CustomComboBox::CustomComboBox(QWidget *parent, bool askOccupy) : QComboBox(parent), askOccupy(askOccupy) {

    }

    CustomComboBox::~CustomComboBox() {
    }

    void CustomComboBox::showPopup() {
        QString current_text = this->currentText();
        QStringList namelist;
        namelist.clear();
        QComboBox::clear();

        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            QSerialPort serial;
            serial.setPort(info);

            if(askOccupy) {
                if (serial.open(QIODevice::ReadWrite)) {//遍历可打开串口
                    namelist.append(serial.portName());
                    serial.close();
                } else {
                    if (serial.portName() == current_text) {//当前串口如果打开也要添加
                        namelist.append(serial.portName());
                    }
                }
            } else {//遍历添加所有串口
                namelist.append(serial.portName());
            }
        }

        QComboBox::addItems(namelist);
        setCurrentText(current_text);
        QComboBox::showPopup();
    }

    void CustomComboBox::setAskOccupy(const bool &flag) {
        askOccupy = flag;
    }
}
