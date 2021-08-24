//
// Created by chiplua on 2021/8/24.
//

#ifndef ELISRS128WINTEST_ELISSENSORTESTWIDGET_H
#define ELISRS128WINTEST_ELISSENSORTESTWIDGET_H

#include <QWidget>
#include "../elisserial/serialport/SerialPort.h"


using namespace ElisSerial;
QT_BEGIN_NAMESPACE
namespace Ui { class ElisSensorTestWidget; }
QT_END_NAMESPACE

class ElisSensorTestWidget : public QWidget {
Q_OBJECT

public:
    explicit ElisSensorTestWidget(QWidget *parent = nullptr, SerialPort *serialPort = 0);
    ~ElisSensorTestWidget() override;

    public slots:
    void btnStartTestPressed();
    void btnStopTestPressed();
    void btnSensortTextExitPressed();

private:
    Ui::ElisSensorTestWidget *ui;
    SerialPort *serialPort1;
    void setHLayoutButtons(Ui::ElisSensorTestWidget *ui);
};


#endif //ELISRS128WINTEST_ELISSENSORTESTWIDGET_H
