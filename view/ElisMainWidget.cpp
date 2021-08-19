//
// Created by chiplua on 2021/8/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ElisMainWidget.h" resolved

#include "ElisMainWidget.h"
#include "ui_ElisMainWidget.h"

void setHLayoutCom(Ui::ElisMainWidget *ui) {
    ui->horizontalLayoutWidget->setStyleSheet("background:rgb(211, 211, 211)");
    ui->hLayoutCom->setSpacing(20);
}

void setVLayoutPassengersLeft(Ui::ElisMainWidget *ui) {
    ui->vLayoutPassenger->setAlignment(Qt::AlignLeft);
    ui->vLayoutPassenger->setSpacing(20);
}

void setVLayoutPassengersRight(Ui::ElisMainWidget *ui) {

}

void setHLayoutPassengers(Ui::ElisMainWidget *ui) {
    ui->horizontalLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    setVLayoutPassengersLeft(ui);
    setVLayoutPassengersRight(ui);
}

void setVLayoutAisleMode(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_3->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnAisleModeSetting->setStyleSheet("background:gray");
    ui->btnAisleModeSetting->setFixedSize((ui->verticalLayoutWidget_6->width() - 40), 20);
    ui->vLayoutAisleMode->setContentsMargins(20, 0, 20, 0);
}

ElisMainWidget::ElisMainWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ElisMainWidget) {
    ui->setupUi(this);

    setHLayoutCom(ui);
    setHLayoutPassengers(ui);
    ui->verticalLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->verticalLayoutWidget_4->setStyleSheet("background:rgb(211, 211, 211)");
    ui->verticalLayoutWidget_5->setStyleSheet("background:rgb(211, 211, 211)");
    ui->verticalLayoutWidget_6->setStyleSheet("background:rgb(211, 211, 211)");
    ui->verticalLayoutWidget_7->setStyleSheet("background:rgb(211, 211, 211)");
    ui->gridLayoutWidget->setStyleSheet("background:rgb(211, 211, 211)");
    ui->gridLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");

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

