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
        void btnOpenComClicked();
        void btnCloseComClicked();
        void btnCurrentStatusRequestPressed();
        void btnOkPressed();
        void btnParamterSettingPressed();
        void btnGateModeSettingPressed();
        void btnAisleModeSettingPressed();
        void btnTestModulePressed();
        void btnTopIndicatorLigthPressed();
        void btnPassageAuthorizationPressed();
        void btnStartStressTestPressed();
        void btnStopStressTestPressed();
        void btnGedModePressed();
        void btnVersionRequestPressed();
        void btnSetEmergencyPressed();
        void btnCancelEmergencyPressed();
        void btnClearPassageCountPressed();
        void btnSensorTestPressed();
        void btnClearInfoPressed();

private:
    Ui::ElisMainWidget *ui;
    QString serialPortName;
    QStringList serialPortsNames;
    SerialPort serialPort;
    void initComboBox(Ui::ElisMainWidget *ui);
    void setHLayoutCom(Ui::ElisMainWidget *ui);
    void setVLayoutPassengersRight(Ui::ElisMainWidget *ui);
    void setHLayoutPassengers(Ui::ElisMainWidget *ui);
    void setVLayoutModeSetting(Ui::ElisMainWidget *ui);
    void setVLayoutAisleMode(Ui::ElisMainWidget *ui);
    void setVLayoutTestParam(Ui::ElisMainWidget *ui);
    void setGLayoutLightSetting(Ui::ElisMainWidget *ui);
    void setPassengerAuthorization(Ui::ElisMainWidget *ui);
    void setGLayoutStressTest(Ui::ElisMainWidget *ui);
    void setNormalFlashGedMode(Ui::ElisMainWidget *ui);
    void setRightButtons(Ui::ElisMainWidget *ui);
};


#endif //ELISRS128WINTEST_ELISMAINWIDGET_H
