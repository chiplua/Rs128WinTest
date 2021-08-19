//
// Created by chiplua on 2021/8/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ElisMainWidget.h" resolved

#include "ElisMainWidget.h"
#include "ui_ElisMainWidget.h"

void setHLayoutCom(Ui::ElisMainWidget *ui) {
    ui->horizontalLayoutWidget->setStyleSheet("background:rgb(211, 211, 211)");
    ui->hLayoutCom->setSpacing(20);
    ui->btnOpenCom->setStyleSheet("background:gray");
    ui->btnCloseCom->setStyleSheet("background:gray");
    ui->btnCurrentStatusRequest->setStyleSheet("background:gray");
    ui->btnOk->setStyleSheet("background:gray");
}

void setVLayoutPassengersLeft(Ui::ElisMainWidget *ui) {
    ui->vLayoutPassengerLeft1->setAlignment(Qt::AlignLeft);
    ui->vLayoutPassengerLeft1->setSpacing(10);
    ui->vLayoutPassengerLeft1->setContentsMargins(5, 5, 0, 5);
    ui->vLayoutPassengerLeft2->setContentsMargins(5, 5, 0, 30);

    ui->tvMaxPassage->setFixedSize(80, 30);
    ui->tvMaxPassage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvMaxPassage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tvFlapClosingTimeout->setFixedSize(80, 30);
    ui->tvFlapClosingTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvFlapClosingTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tvPassengerAuthorizationTimeout->setFixedSize(80, 30);
    ui->tvPassengerAuthorizationTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvPassengerAuthorizationTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void setVLayoutPassengersRight(Ui::ElisMainWidget *ui) {
    ui->vLayoutPassengerRight1->setAlignment(Qt::AlignLeft);
    ui->vLayoutPassengerRight1->setSpacing(10);
    ui->vLayoutPassengerRight1->setContentsMargins(0, 5, 5, 5);
    ui->vLayoutPassengerRight2->setContentsMargins(0, 10, 5, 30);

    ui->tvSensorTimeout->setFixedSize(80, 30);
    ui->tvSensorTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvSensorTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tvLeaveAisleTimeout->setFixedSize(80, 30);
    ui->tvLeaveAisleTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvLeaveAisleTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tvOpenSafetyTimeout->setFixedSize(80, 30);
    ui->tvOpenSafetyTimeout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvOpenSafetyTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->btnParameterSetting->setStyleSheet("background:gray");
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
    ui->vLayoutModeSetting->setContentsMargins(20, 40, 20, 0);
}

void setVLayoutAisleMode(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_3->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnAisleModeSetting->setStyleSheet("background:gray");
    ui->btnAisleModeSetting->setFixedSize((ui->verticalLayoutWidget_6->width() - 40), 20);
    ui->vLayoutAisleMode->setContentsMargins(20, 0, 20, 10);
}

void setVLayoutTestParam(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_4->setStyleSheet("background:rgb(211, 211, 211)");
    ui->tvTestParam->setFixedSize(40, 30);
    ui->btnTestModule->setStyleSheet("background:gray");
    ui->btnTestModule->setFixedSize((ui->verticalLayoutWidget_4->width() - 30), 20);
    ui->vLayoutTestParam->setContentsMargins(20, 20, 20, 25);
}

void setGLayoutLightSetting(Ui::ElisMainWidget *ui) {
    ui->gridLayoutWidget->setStyleSheet("background:rgb(211, 211, 211)");
    ui->gLayoutLight->setContentsMargins(20, 15, 20, 15);

    ui->tvLightDuration->setFixedSize(200, 30);;
    ui->tvLightDuration->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvLightDuration->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tvFlashPeriod->setFixedSize(200, 30);
    ui->tvFlashPeriod->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvFlapClosingTimeout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->btnTopIndicatorLight->setStyleSheet("background:gray");
}

void setPassengerAuthorization(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_5->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnPassageAuthorization->setStyleSheet("background:gray");
    ui->btnPassageAuthorization->setFixedSize((ui->verticalLayoutWidget_5->width() - 40), 20);
    ui->vLayoutPassengerAuthorization->setContentsMargins(25, 0, 25, 15);
}

void setGLayoutStressTest(Ui::ElisMainWidget *ui) {
    ui->gridLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->gLayoutStressTest->setContentsMargins(20, 20, 20, 20);

    ui->btnStartStressTest->setStyleSheet("background:gray");
    ui->btnStopStressTest->setStyleSheet("background:gray");

    ui->tvStressTestIntervalTime->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvStressTestIntervalTime->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tvEntryTotal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvEntryTotal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tvExitTotal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvExitTotal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

ElisMainWidget::ElisMainWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ElisMainWidget) {
    ui->setupUi(this);

    setHLayoutCom(ui);
    setHLayoutPassengers(ui);
    setVLayoutModeSetting(ui);
    setVLayoutTestParam(ui);
    setGLayoutLightSetting(ui);
    setPassengerAuthorization(ui);
    setGLayoutStressTest(ui);

    ui->verticalLayoutWidget_6->setStyleSheet("background:rgb(211, 211, 211)");
    ui->verticalLayoutWidget_7->setStyleSheet("background:rgb(211, 211, 211)");

    ui->tvExitTotal->setStyleSheet("background:white");
    ui->tvEntryTotal->setStyleSheet("background:white");
    ui->tvFlapClosingTimeout->setStyleSheet("background:white");
    ui->tvFlashPeriod->setStyleSheet("background:white");
    ui->tvLeaveAisleTimeout->setStyleSheet("background:white");
    ui->tvEntryTotal->setStyleSheet("background:white");
    ui->tvLightDuration->setStyleSheet("background:white");
    ui->tvMaxPassage->setStyleSheet("background:white");
    ui->tvOpenSafetyTimeout->setStyleSheet("background:white");
    ui->tvPassengerAuthorizationTimeout->setStyleSheet("background:white");
    ui->tvSensorTimeout->setStyleSheet("background:white");
    ui->tvStressTestIntervalTime->setStyleSheet("background:white");
    ui->tvTestParam->setStyleSheet("background:white");
    ui->cbComList->setStyleSheet("background:white");
    ui->cbExitMode->setStyleSheet("background:white");
    ui->cbTopIndicatorLight->setStyleSheet("background:white");
    ui->cbTestModule->setStyleSheet("background:white");
    setVLayoutAisleMode(ui);
}

ElisMainWidget::~ElisMainWidget() {
    delete ui;
}

