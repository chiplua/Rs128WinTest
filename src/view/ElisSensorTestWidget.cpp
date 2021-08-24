//
// Created by chiplua on 2021/8/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ElisSensorTestWidget.h" resolved

#include "ElisSensorTestWidget.h"
#include "ui_ElisSensorTestWidget.h"

void setHLayoutButtons(Ui::ElisSensorTestWidget *ui) {
    ui->hLayoutButtons->setContentsMargins(20, 20, 20, 20);
}

void setLeftSensors(Ui::ElisSensorTestWidget *ui) {
    const QString styleStr = "min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:green";
    ui->lbS1->setStyleSheet(styleStr);
    ui->lbS2->setStyleSheet(styleStr);
    ui->lbS3->setStyleSheet(styleStr);
    ui->lbS4->setStyleSheet(styleStr);
    ui->lbS5->setStyleSheet(styleStr);
}

void setMiddle1Sensors(Ui::ElisSensorTestWidget *ui) {
    const QString styleStr = "min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:green";
    ui->lbS6->setStyleSheet(styleStr);
    ui->lbS7->setStyleSheet(styleStr);
    ui->lbS8->setStyleSheet(styleStr);
    ui->lbS9->setStyleSheet(styleStr);
}

void setMiddle2Sensors(Ui::ElisSensorTestWidget *ui) {
    const QString styleStr = "min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:green";
    ui->lbS10->setStyleSheet(styleStr);
    ui->lbS11->setStyleSheet(styleStr);
    ui->lbS12->setStyleSheet(styleStr);
    ui->lbS13->setStyleSheet(styleStr);
}

void setRightSensors(Ui::ElisSensorTestWidget *ui) {
    const QString styleStr = "min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:green";
    ui->lbS14->setStyleSheet(styleStr);
    ui->lbS15->setStyleSheet(styleStr);
    ui->lbS16->setStyleSheet(styleStr);
    ui->lbS17->setStyleSheet(styleStr);
    ui->lbS18->setStyleSheet(styleStr);
}

ElisSensorTestWidget::ElisSensorTestWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ElisSensorTestWidget) {
    ui->setupUi(this);

    setHLayoutButtons(ui);
    setLeftSensors(ui);
    setMiddle1Sensors(ui);
    setMiddle2Sensors(ui);
    setRightSensors(ui);
}

ElisSensorTestWidget::~ElisSensorTestWidget() {
    delete ui;
}

