//
// Created by chiplua on 2021/8/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ElisSensorTestWidget.h" resolved

#include <QDebug>
#include "ElisSensorTestWidget.h"
#include "ui_ElisSensorTestWidget.h"
#include "../../src/elisserial/parsedata/PackagingAndUnpacking.h"

using namespace ElisSerial;

void ElisSensorTestWidget::btnStartTestPressed() {
    qDebug() << "start test pressed";
    //02 04 05 10 10 10 02 00 13 03
    std::vector<unsigned char> sensorTestStartCommandVect = PackagingAndUnpacking::requestTestSensor(0x0a, 0x0a, 0x00);

    unsigned char array[sensorTestStartCommandVect.size()];
    std::copy(sensorTestStartCommandVect.begin(), sensorTestStartCommandVect.end(), array);
    QByteArray qba = QByteArray::fromRawData(reinterpret_cast<char*>(array), sensorTestStartCommandVect.size());
    serialPort1->write(qba);
}


void ElisSensorTestWidget::btnStopTestPressed() {
    qDebug() << "stop test pressed";
    //02 04 05 12 00 00 13 03
    std::vector<unsigned char> sensorTestCancelCommandVect = PackagingAndUnpacking::requestStopCurrentTest(0x05, 0x00);

    unsigned char array[sensorTestCancelCommandVect.size()];
    std::copy(sensorTestCancelCommandVect.begin(), sensorTestCancelCommandVect.end(), array);
    QByteArray qba = QByteArray::fromRawData(reinterpret_cast<char*>(array), sensorTestCancelCommandVect.size());
    serialPort1->write(qba);
}

void ElisSensorTestWidget::btnSensortTextExitPressed() {
    qDebug() << "exit pressed";
    this->close();
}

void ElisSensorTestWidget::setHLayoutButtons(Ui::ElisSensorTestWidget *ui) {
    ui->hLayoutButtons->setContentsMargins(20, 20, 20, 20);
    connect(ui->btnStartTest, SIGNAL(clicked()), this, SLOT(btnStartTestPressed()));
    connect(ui->btnStopTest, SIGNAL(clicked()), this, SLOT(btnStopTestPressed()));
    connect(ui->btnSensorTestExit, SIGNAL(clicked()), this, SLOT(btnSensortTextExitPressed()));
}

void setLeftSensors(Ui::ElisSensorTestWidget *ui, QString s1Color, QString s2Color, QString s3Color, QString s4Color, QString s5Color) {
    const QString styleBaseStr = "font-size:10px;min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:";
    ui->lbS1->setStyleSheet(styleBaseStr + s1Color);
    ui->lbS2->setStyleSheet(styleBaseStr + s2Color);
    ui->lbS3->setStyleSheet(styleBaseStr + s3Color);
    ui->lbS4->setStyleSheet(styleBaseStr + s4Color);
    ui->lbS5->setStyleSheet(styleBaseStr + s5Color);
}

void setMiddle1Sensors(Ui::ElisSensorTestWidget *ui, QString s6Color, QString s7Color, QString s8Color, QString s9Color) {
    const QString styleBaseStr = "font-size:10px;min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:";
    ui->lbS6->setStyleSheet(styleBaseStr + s6Color);
    ui->lbS7->setStyleSheet(styleBaseStr + s7Color);
    ui->lbS8->setStyleSheet(styleBaseStr + s8Color);
    ui->lbS9->setStyleSheet(styleBaseStr + s9Color);
}

void setMiddle2Sensors(Ui::ElisSensorTestWidget *ui, QString s10Color, QString s11Color, QString s12Color, QString s13Color) {
    const QString styleBaseStr = "font-size:10px;min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:";
    ui->lbS10->setStyleSheet(styleBaseStr + s10Color);
    ui->lbS11->setStyleSheet(styleBaseStr + s11Color);
    ui->lbS12->setStyleSheet(styleBaseStr + s12Color);
    ui->lbS13->setStyleSheet(styleBaseStr + s13Color);
}

void setRightSensors(Ui::ElisSensorTestWidget *ui, QString s14Color, QString s15Color, QString s16Color, QString s17Color, QString s18Color) {
    const QString styleBaseStr = "font-size:10px;min-width:20px;min-height:20px;max-width:20px;max-height:20px;border-radius:10px;border:1px solid black;background:";
    ui->lbS14->setStyleSheet(styleBaseStr + s14Color);
    ui->lbS15->setStyleSheet(styleBaseStr + s15Color);
    ui->lbS16->setStyleSheet(styleBaseStr + s16Color);
    ui->lbS17->setStyleSheet(styleBaseStr + s17Color);
    ui->lbS18->setStyleSheet(styleBaseStr + s18Color);
}

ElisSensorTestWidget::ElisSensorTestWidget(QWidget *parent, SerialPort *serialPort) :
        QWidget(parent), ui(new Ui::ElisSensorTestWidget) {
    ui->setupUi(this);
    serialPort1 = serialPort;

    setHLayoutButtons(ui);
    setLeftSensors(ui, "green", "green", "green", "green", "green");
    setMiddle1Sensors(ui, "green", "green", "green", "green");
    setMiddle2Sensors(ui, "green", "green", "green", "green");
    setRightSensors(ui, "green", "green", "green", "green", "green");
}

ElisSensorTestWidget::~ElisSensorTestWidget() {
    delete ui;
}

