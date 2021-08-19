//
// Created by chiplua on 2021/8/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ElisMainWidget.h" resolved

#include <QSerialPortInfo>
#include "ElisMainWidget.h"
#include "ui_ElisMainWidget.h"
#include <QDebug>

QPalette getButtonCommonPalette() {
    QPalette pal;
    pal.setColor(QPalette::ButtonText, QColor(255,255,255));

    return pal;
}

void ElisMainWidget::cbComListChanged(int i) {
    qDebug() << "cbComListChanged: i = %d, strList = %s" << i;
    serialPortName = serialPortsNames.at(i);
    qDebug() << "You select serial port %s " << serialPortName;
    bool isOpendSuccess = serialPort.openPort(serialPortName);
    qDebug() << serialPortName << " opened " << isOpendSuccess;

    if (isOpendSuccess) {
        ui->tbDisplayInfo->append(serialPortName + "open success");
    } else {
        ui->tbDisplayInfo->append(serialPortName + "open fail");
    }
}

void ElisMainWidget::initComboBox(Ui::ElisMainWidget *ui) {
            foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();
            qDebug() << "Serial Number: " << info.serialNumber();
            qDebug() << "System Location: " << info.systemLocation();

            serialPortsNames << info.portName();
        }

    ui->cbComList->clear();
    ui->cbComList->addItems(serialPortsNames);

    if (ui->cbComList->count() == 1) {
        serialPortName = serialPortsNames.at(0);
        qDebug() << "You select serial port %s " << serialPortName;
        bool isOpendSuccess = serialPort.openPort(serialPortName);
        qDebug() << serialPortName << " opened " << isOpendSuccess;
        ui->tbDisplayInfo->append(serialPortName + " open " + (isOpendSuccess ? "success" : "fail"));
    } else {
        connect(ui->cbComList, SIGNAL(currentIndexChanged(int)), this, SLOT(cbComListChanged(int)));
    }
}

void ElisMainWidget::setHLayoutCom(Ui::ElisMainWidget *ui) {
    ui->horizontalLayoutWidget->setStyleSheet("background:rgb(211, 211, 211)");
    ui->hLayoutCom->setSpacing(20);
    ui->btnOpenCom->setStyleSheet("background:gray");
    ui->btnOpenCom->setPalette(getButtonCommonPalette());
    ui->btnCloseCom->setStyleSheet("background:gray");
    ui->btnCloseCom->setPalette(getButtonCommonPalette());
    ui->btnCurrentStatusRequest->setStyleSheet("background:gray");
    ui->btnCurrentStatusRequest->setPalette(getButtonCommonPalette());
    ui->btnOk->setStyleSheet("background:gray");
    ui->btnOk->setPalette(getButtonCommonPalette());
    ui->cbComList->setStyleSheet("background:white");
    ElisMainWidget::initComboBox(ui);
}

void setVLayoutPassengersLeft(Ui::ElisMainWidget *ui) {
    ui->vLayoutPassengerLeft1->setAlignment(Qt::AlignLeft);
    ui->vLayoutPassengerLeft1->setSpacing(10);
    ui->vLayoutPassengerLeft1->setContentsMargins(5, 5, 0, 5);
    ui->vLayoutPassengerLeft2->setContentsMargins(5, 5, 0, 30);

    ui->tvMaxPassage->setFixedSize(80, 30);
    ui->tvMaxPassage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvMaxPassage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvMaxPassage->setStyleSheet("background:white");

    ui->tvFlapClosingTimeout->setFixedSize(80, 30);
    ui->tvFlapClosingTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvFlapClosingTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvFlapClosingTimeout->setStyleSheet("background:white");

    ui->tvPassengerAuthorizationTimeout->setFixedSize(80, 30);
    ui->tvPassengerAuthorizationTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvPassengerAuthorizationTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvPassengerAuthorizationTimeout->setStyleSheet("background:white");
}

void setVLayoutPassengersRight(Ui::ElisMainWidget *ui) {
    ui->vLayoutPassengerRight1->setAlignment(Qt::AlignLeft);
    ui->vLayoutPassengerRight1->setSpacing(10);
    ui->vLayoutPassengerRight1->setContentsMargins(0, 5, 5, 5);
    ui->vLayoutPassengerRight2->setContentsMargins(0, 10, 5, 30);

    ui->tvSensorTimeout->setFixedSize(80, 30);
    ui->tvSensorTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvSensorTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvSensorTimeout->setStyleSheet("background:white");

    ui->tvLeaveAisleTimeout->setFixedSize(80, 30);
    ui->tvLeaveAisleTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvLeaveAisleTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvLeaveAisleTimeout->setStyleSheet("background:white");

    ui->tvOpenSafetyTimeout->setFixedSize(80, 30);
    ui->tvOpenSafetyTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvOpenSafetyTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvOpenSafetyTimeout->setStyleSheet("background:white");

    ui->btnParameterSetting->setStyleSheet("background:gray");
    ui->btnParameterSetting->setPalette(getButtonCommonPalette());
}

void setHLayoutPassengers(Ui::ElisMainWidget *ui) {
    ui->horizontalLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->hLayoutPassenger->setSpacing(5);
    setVLayoutPassengersLeft(ui);
    setVLayoutPassengersRight(ui);
}

void setVLayoutModeSetting(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnGateModeSetting->setStyleSheet("background:gray");
    ui->btnGateModeSetting->setFixedSize((ui->verticalLayoutWidget_2->width() - 30), 20);
    ui->btnGateModeSetting->setPalette(getButtonCommonPalette());
    ui->vLayoutModeSetting->setContentsMargins(20, 40, 20, 0);
    ui->cbExitMode->setStyleSheet("background:white");
}

void setVLayoutAisleMode(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_3->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnAisleModeSetting->setStyleSheet("background:gray");
    ui->btnAisleModeSetting->setFixedSize((ui->verticalLayoutWidget_6->width() - 40), 20);
    ui->btnAisleModeSetting->setPalette(getButtonCommonPalette());
    ui->vLayoutAisleMode->setContentsMargins(20, 50, 20, 25);
}

void setVLayoutTestParam(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_4->setStyleSheet("background:rgb(211, 211, 211)");
    ui->tvTestParam->setFixedSize(40, 30);
    ui->tvTestParam->setStyleSheet("background:white");

    ui->btnTestModule->setStyleSheet("background:gray");
    ui->btnTestModule->setFixedSize((ui->verticalLayoutWidget_4->width() - 30), 20);
    ui->btnTestModule->setPalette(getButtonCommonPalette());
    ui->vLayoutTestParam->setContentsMargins(20, 20, 20, 25);
    ui->cbTestModule->setStyleSheet("background:white");
}

void setGLayoutLightSetting(Ui::ElisMainWidget *ui) {
    ui->gridLayoutWidget->setStyleSheet("background:rgb(211, 211, 211)");
    ui->gLayoutLight->setContentsMargins(20, 15, 20, 15);

    ui->tvLightDuration->setFixedSize(200, 30);;
    ui->tvLightDuration->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvLightDuration->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvLightDuration->setStyleSheet("background:white");

    ui->tvFlashPeriod->setFixedSize(200, 30);
    ui->tvFlashPeriod->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvFlashPeriod->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvFlashPeriod->setStyleSheet("background:white");

    ui->btnTopIndicatorLight->setStyleSheet("background:gray");
    ui->btnTopIndicatorLight->setPalette(getButtonCommonPalette());
    ui->cbTopIndicatorLight->setStyleSheet("background:white");
}

void setPassengerAuthorization(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_5->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnPassageAuthorization->setStyleSheet("background:gray");
    ui->btnPassageAuthorization->setFixedSize((ui->verticalLayoutWidget_5->width() - 30), 20);
    ui->btnPassageAuthorization->setPalette(getButtonCommonPalette());
    ui->vLayoutPassengerAuthorization->setContentsMargins(20, 0, 20, 15);
}

void setGLayoutStressTest(Ui::ElisMainWidget *ui) {
    ui->gridLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->gLayoutStressTest->setContentsMargins(20, 20, 20, 20);

    ui->btnStartStressTest->setStyleSheet("background:gray");
    ui->btnStartStressTest->setPalette(getButtonCommonPalette());
    ui->btnStopStressTest->setStyleSheet("background:gray");
    ui->btnStopStressTest->setPalette(getButtonCommonPalette());

    ui->tvStressTestIntervalTime->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvStressTestIntervalTime->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvStressTestIntervalTime->setStyleSheet("background:white");

    ui->tvEntryTotal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvEntryTotal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvEntryTotal->setStyleSheet("background:white");

    ui->tvExitTotal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvExitTotal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvExitTotal->setStyleSheet("background:white");
}

void setNormalFlashGedMode(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_6->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnGedMode->setStyleSheet("background:gray");
    ui->btnGedMode->setFixedSize((ui->verticalLayoutWidget_5->width() - 30), 20);
    ui->btnGedMode->setPalette(getButtonCommonPalette());
    ui->vLayoutNormalFlashGedMode->setContentsMargins(20, 0, 20, 15);
}

void setRightButtons(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_7->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnVersionRequest->setStyleSheet("background:gray");
    ui->btnVersionRequest->setPalette(getButtonCommonPalette());
    ui->btnSetEmergency->setStyleSheet("background:gray");
    ui->btnSetEmergency->setPalette(getButtonCommonPalette());
    ui->btnCancelEmergency->setStyleSheet("background:gray");
    ui->btnCancelEmergency->setPalette(getButtonCommonPalette());
    ui->btnClearPassageCount->setStyleSheet("background:gray");
    ui->btnClearPassageCount->setPalette(getButtonCommonPalette());
    ui->btnSensortest->setStyleSheet("background:gray");
    ui->btnSensortest->setPalette(getButtonCommonPalette());
    ui->btnClearInfo->setStyleSheet("background:gray");
    ui->btnClearInfo->setPalette(getButtonCommonPalette());
    ui->vLayoutRightButtons->setContentsMargins(20, 10, 20, 10);
}

ElisMainWidget::ElisMainWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ElisMainWidget) {
    ui->setupUi(this);

    setHLayoutCom(ui);
    setHLayoutPassengers(ui);
    setVLayoutModeSetting(ui);
    setVLayoutAisleMode(ui);
    setVLayoutTestParam(ui);
    setGLayoutLightSetting(ui);
    setPassengerAuthorization(ui);
    setGLayoutStressTest(ui);
    setNormalFlashGedMode(ui);
    setRightButtons(ui);
}

ElisMainWidget::~ElisMainWidget() {
    delete ui;
}

