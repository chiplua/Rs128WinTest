//
// Created by chiplua on 2021/8/18.
//

#ifndef ELISRS128WINTEST_ELISMAINWIDGET_H
#define ELISRS128WINTEST_ELISMAINWIDGET_H

#include <QWidget>
#include "../serialport/SerialPort.h"

using namespace ElisSerial;
QT_BEGIN_NAMESPACE
namespace Ui { class ElisMainWidget; }
QT_END_NAMESPACE

class ElisMainWidget : public QWidget {
Q_OBJECT

public:
    explicit ElisMainWidget(QWidget *parent = nullptr);
    ~ElisMainWidget() override;
    public slots:
        void cbComListChanged(int i);

private:
    Ui::ElisMainWidget *ui;
    void initComboBox(Ui::ElisMainWidget *ui);
    void setHLayoutCom(Ui::ElisMainWidget *ui);
    QString serialPortName;
    QStringList serialPortsNames;
    SerialPort serialPort;
};


#endif //ELISRS128WINTEST_ELISMAINWIDGET_H
