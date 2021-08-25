//
// Created by chiplua on 2021/8/25.
//

#ifndef ELISRS128WINTEST_CUSTOMCOMBOBOX_H
#define ELISRS128WINTEST_CUSTOMCOMBOBOX_H

#include <QComboBox>
#include <QTSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>

namespace ElisView {
    class CustomComboBox : public QComboBox {
        Q_OBJECT

    public:
        explicit CustomComboBox(QWidget *parent = nullptr, bool askOccupy = 0);
        ~CustomComboBox()override;

        void showPopup()override;
        void setAskOccupy(const bool &flag);

    private:
        bool askOccupy;
    };
}
#endif //ELISRS128WINTEST_CUSTOMCOMBOBOX_H
