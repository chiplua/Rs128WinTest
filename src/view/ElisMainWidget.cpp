//
// Created by chiplua on 2021/8/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ElisMainWidget.h" resolved

#include <QSerialPortInfo>
#include "ElisMainWidget.h"
#include "ui_ElisMainWidget.h"
#include <QDebug>
#include <QMessageBox>
#include "ComboListContent.h"
#include "../elisserial/parsedata/PackagingAndUnpacking.h"
#include "../utils/StringUtils.h"
#include "ElisSensorTestWidget.h"

using namespace ElisView;
using namespace ElisSerial;
using namespace ElisTool;



QPalette getButtonCommonPalette() {
    QPalette pal;
    pal.setColor(QPalette::ButtonText, QColor(255,255,255));

    return pal;
}

void vector2QByteArray(const std::vector<unsigned char> vect, unsigned char array[], QByteArray *qba) {
    std::copy(vect.begin(), vect.end(), array);

    *qba = QByteArray::fromRawData(reinterpret_cast<char*>(array), vect.size());
}

void ElisMainWidget::disconnectAll() {
    disconnect(&serialPort, SIGNAL(readyRead()), this, SLOT(receiveComVersion()));

}

void ElisMainWidget::receiveComVersion() {
    QByteArray bufferData = serialPort.readAll();
    //QByteArray bufferData = serialPort.read(1);
    qDebug() << "receiveComVersion bufferData = " + bufferData.toHex();

    //qDebug()<<temp;
    if ((bufferData.at(0) == 0x02) && bufferData.size() == 1) {
        //return;
        pasteData.append(bufferData);
    }


    //第一种：有头无尾，先清空原有内容，再附加
    if ((bufferData.at(0) == 0x02) && (bufferData.at(bufferData.size() - 1) != 0x03) && bufferData.size() != 1) {
        //pasteData.clear();
        pasteData.append(bufferData);
        qDebug() << "after receiveComVersion1 pastData = " + pasteData.toHex();
    }

    //第二种：无头无尾且变量已有内容，数据中段部分，继续附加即可
    if ((bufferData.at(0) != 0x02) && (bufferData.at(bufferData.size() - 1) != 0x03) && (!pasteData.isNull())) {
        pasteData.append(bufferData);
        qDebug() << "after receiveComVersion2 pastData = " + pasteData.toHex();
    }

    //第3种：无头有尾
    if ((bufferData.at(0) != 0x02) && (bufferData.at(bufferData.size() - 1) == 0x03) && (!pasteData.isNull())) {
        pasteData.append(bufferData);
        qDebug() << "after receiveComVersion33 pastData = " + pasteData.toHex();
    }

    if ((bufferData.at(0) == 0x02 && bufferData.at(bufferData.size() - 1) == 0x03)) {
        pasteData.append(bufferData);
        qDebug() << "after receiveComVersion3 pastData = " + pasteData.toHex();
    }

    //第四2种：有头有尾, 需判断是否为一段完整的内容
    if (bufferData.contains(0x02) && bufferData.contains(0x03)) {
        qDebug() << "after receiveComVersion4 pastData = " + pasteData.toHex();

        QByteArray cutArray;
        int needRemoveSize = 0;
        for (int i = 0; i < pasteData.size(); i++) {
            if (pasteData.at(i) != 0x03) {
                cutArray.append(pasteData.at(i));
            } else {
                cutArray.append(pasteData.at(i));
                qDebug() << "cutArray2 = " << cutArray.toHex();
                if (cutArray.at(0) != 0x02) {
                    readData.clear();
                    pasteData.clear();
                    ui->tbDisplayInfo->append("received error data");
                    qDebug() << "received error data";

                    return;
                } else {
                    if (cutArray.at(1) == 0x02) {
                        cutArray.remove(1, 1);
                    }
                }

                //std::vector<unsigned char> resultVect = PackagingAndUnpacking::convertReceivedArray2OnlyLenDataBcc(reinterpret_cast<unsigned char*>(pasteData.data()), pasteData.size());
                std::vector<unsigned char> resultVect = PackagingAndUnpacking::convertReceivedArray2OnlyLenDataBcc(reinterpret_cast<unsigned char*>(cutArray.data()), cutArray.size());
                if (resultVect.size() > 0) {
                    bool isBccRight = StringUtils::isBccRight(resultVect, resultVect.at(resultVect.size() - 1));
                    qDebug() << "resultVect2 = " << resultVect;
                    qDebug() << "resultVect2 bcc right = " << isBccRight;

                    if (isBccRight) {
                        int shouldLength = resultVect.at(0) + 4;
                        int realLength = resultVect.size() + 2;
                        if (shouldLength != realLength) { //有头有尾，但不是完整数据，继续添加
                        } else {//有头有尾（一段完整的内容），先清空原有内容，再附加，然后输出，最后清空变量
                            //pasteData.clear();
                            readData = cutArray;
                        }

                        if (!readData.isEmpty()) {
                            QByteArray hexData = readData.toHex();
                            qDebug() << "hexData2.at(0) = " << readData.at(0);
                            qDebug() << "hexData2.at(last) = " << readData.at(readData.length() - 1);
                            qDebug() << "hexData2.size() = " << readData.size();
                            QString str;
                            str.prepend(hexData);// QByteArray转QString方法2
                            QString disStr;
                            for (int i = 0; i < str.length(); i+=2) {
                                QString st = str.mid(i,2);
                                disStr += st;
                                disStr += " ";
                            }
                            ui->tbDisplayInfo->append(disStr);

                            readData.clear();
                            needRemoveSize = needRemoveSize + cutArray.size();
                            cutArray.clear();
                        }
                    }
                }
            }
            if (cutArray.size() > 0) {
                if (cutArray.at(0) != 0x02) {
                    cutArray.clear();
                    continue;
                }
            }

        }

        qDebug() << "the follow data will be delete: " << pasteData.mid(0, needRemoveSize).toHex();
        pasteData.remove(0, needRemoveSize);
        qDebug() << "pasterData left: " << pasteData.toHex();
    }

    qDebug() << "emit result ready";
    emit resultReady(0);
}

void ElisMainWidget::serialWriteData(QByteArray qba) {
    if (serialPort.isOpen()) {
        serialPort.write(qba);
    } else {
        QMessageBox::information(NULL, "Serial port wait connect", "Serial port not open.",
                                 QMessageBox::Yes, QMessageBox::Yes);

    }

}

void ElisMainWidget::btnOpenComClicked() {
    ui->tbDisplayInfo->append("Open the com port pressed");
    bool isOpendSuccess = serialPort.openPort(serialPortName);
    qDebug() << serialPortName << " opened " << isOpendSuccess;

    if (isOpendSuccess) {
        ui->tbDisplayInfo->append(serialPortName + " open success");
    } else {
        ui->tbDisplayInfo->append(serialPortName + " open fail");
    }
}

void ElisMainWidget::btnCloseComClicked() {
    ui->tbDisplayInfo->append("Close the com port pressed");
    disconnectAll();
    serialPort.close();
    qDebug() << serialPortName << " closed";
}

void ElisMainWidget::btnCurrentStatusRequestPressed() {
    ui->tbDisplayInfo->append("Current status request button pressed");
    std::vector<unsigned char> statusVect = PackagingAndUnpacking::requestStatus(0);
    QByteArray qba;
    unsigned char array[statusVect.size()];
    vector2QByteArray(statusVect, array, &qba);

    //qDebug() << qa << qa.toHex() << qa.size();
    serialWriteData(qba);
}

void ElisMainWidget::btnOkPressed() {
    ui->tbDisplayInfo->append("Ok button pressed");
    QApplication *app;
    app->quit();
}

void ElisMainWidget::btnParamterSettingPressed() {
    ui->tbDisplayInfo->append("Parameter setting pressed");
    //02 0D 01 05 00 10 02 00 1E 3C 10 03 01 00 00 00 00 2B 03
    std::vector<unsigned char> parametersVect = PackagingAndUnpacking::requestConfigParameters(0x01,
                                                                                               0x00,
                                                                                               0x02,
                                                                                               0x00,
                                                                                               0x1E,
                                                                                               0x3c,
                                                                                               0x03,
                                                                                               0x01,
                                                                                               0x00,
                                                                                               0x00,
                                                                                               0x00,
                                                                                               0x00);

    QByteArray qba;
    unsigned char array[parametersVect.size()];
    vector2QByteArray(parametersVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnGateModeSettingPressed() {
    ui->tbDisplayInfo->append("Gate mode setting pressed");
    //02 10 03 10 02 06 04 10 03 03 error
    std::vector<unsigned char> gateModeVect = PackagingAndUnpacking::requestSetGateMode(0x02, 0x02);

    QByteArray qba;
    unsigned char array[gateModeVect.size()];
    vector2QByteArray(gateModeVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnAisleModeSettingPressed() {
    ui->tbDisplayInfo->append("Aisle mode setting pressed");
    //02 10 03 10 03 07 01 06 03
    std::vector<unsigned char> aisleModeVect = PackagingAndUnpacking::requestSetAisleMode(0x03, 0x02);

    QByteArray qba;
    unsigned char array[aisleModeVect.size()];
    vector2QByteArray(aisleModeVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnTestModulePressed() {
    ui->tbDisplayInfo->append("Test module pressed");
    //02 04 05 0A 00 00 0B 03
    std::vector<unsigned char> testModuleVect = PackagingAndUnpacking::requestTestModule(0x04, 0x01, 0x00);

    QByteArray qba;
    unsigned char array[testModuleVect.size()];
    vector2QByteArray(testModuleVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnTopIndicatorLigthPressed() {
    ui->tbDisplayInfo->append("Top indicator light pressed");
    //02 05 06 0B 00 01 00 09 03
    std::vector<unsigned char> topIndicatorLightVect = PackagingAndUnpacking::requestTopIndicatorLight(0x05,
                                                                                                0x00,
                                                                                                0x01,
                                                                                                0x00);

    QByteArray qba;
    unsigned char array[topIndicatorLightVect.size()];
    vector2QByteArray(topIndicatorLightVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnPassageAuthorizationPressed() {
    ui->tbDisplayInfo->append("Passage authorization pressed");
    //02 10 03 04 04 01 10 02 03
    std::vector<unsigned char> passageAuthorizationVect = PackagingAndUnpacking::requestPassageAuthorization(0x04, 0x01);

    QByteArray qba;
    unsigned char array[passageAuthorizationVect.size()];
    vector2QByteArray(passageAuthorizationVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnStartStressTestPressed() {
    ui->tbDisplayInfo->append("Start stress test pressed");
}

void ElisMainWidget::btnStopStressTestPressed() {
    ui->tbDisplayInfo->append("Stop stress test pressed");
}

void ElisMainWidget::btnGedModePressed() {
    ui->tbDisplayInfo->append("Ged mode pressed");
    //02 10 03 0c 0c 00 10 03 03
    std::vector<unsigned char> setGedModeCommandVect = PackagingAndUnpacking::requestSetGedMode(0x0C, 0x00);

    QByteArray qba;
    unsigned char array[setGedModeCommandVect.size()];
    vector2QByteArray(setGedModeCommandVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnVersionRequestPressed() {
    ui->tbDisplayInfo->append("Version request pressed");
    //02 10 02 08 08 10 02 03
    std::vector<unsigned char> versionCommandVect = PackagingAndUnpacking::requestVersion(0x08);

    QByteArray qba;
    unsigned char array[versionCommandVect.size()];
    vector2QByteArray(versionCommandVect, array, &qba);
    serialWriteData(qba);
    disconnectAll();
    connect(&serialPort, SIGNAL(readyRead()), this, SLOT(receiveComVersion()), Qt::QueuedConnection);
    //connect(&serialPort, SIGNAL(readyRead()), this, SLOT(receiveComVersion()));

}

void ElisMainWidget::btnSetEmergencyPressed() {
    ui->tbDisplayInfo->append("Set emergency pressed");
    //02 10 03 07 0D 01 08 03
    std::vector<unsigned char> setEmergencyVect = PackagingAndUnpacking::requestEmergency(0x07, 0x01);

    QByteArray qba;
    unsigned char array[setEmergencyVect.size()];
    vector2QByteArray(setEmergencyVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnCancelEmergencyPressed() {
    ui->tbDisplayInfo->append("Cancel emergency pressed");
    //02 10 03 07 0E 10 02 08 03
    std::vector<unsigned char> cancelEmergencyVect = PackagingAndUnpacking::requestEmergency(0x07, 0x02);

    QByteArray qba;
    unsigned char array[cancelEmergencyVect.size()];
    vector2QByteArray(cancelEmergencyVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnClearPassageCountPressed() {
    ui->tbDisplayInfo->append("Clear passage count pressed");
    //02 10 03 0b 0b 00 10 03 03
    std::vector<unsigned char> clearPassageCountVect = PackagingAndUnpacking::requestClearPasssageCount(0x0B, 0x00);

    QByteArray qba;
    unsigned char array[clearPassageCountVect.size()];
    vector2QByteArray(clearPassageCountVect, array, &qba);
    serialWriteData(qba);
}

void ElisMainWidget::btnSensorTestPressed() {
    ui->tbDisplayInfo->append("Sensor test pressed");
    if (serialPort.isOpen()) {
        ElisSensorTestWidget *sensorTestWidget = new ElisSensorTestWidget(this->parentWidget(), &serialPort);
        sensorTestWidget->setWindowModality(Qt::ApplicationModal);//设置子窗口打开后禁止操作母窗口
        sensorTestWidget->show();
    } else {
        QMessageBox::information(NULL, "Serial port wait connect", "Serial port not open.",
                                 QMessageBox::Yes, QMessageBox::Yes);
    }
}

void ElisMainWidget::btnClearInfoPressed() {
    ui->tbDisplayInfo->clear();
}

void ElisMainWidget::cbComListChanged(int i) {
    qDebug() << "cbComListChanged: i = %d, strList = %s" << i;
    serialPortName = serialPortsNames.at(i);
    qDebug() << "You select serial port %s " << serialPortName;
}

void ElisMainWidget::cbModesChanged(int index) {
    ui->tbDisplayInfo->append("ComboBox modes changed");
}

void ElisMainWidget::cbTestModuleChanged(int index) {
    ui->tbDisplayInfo->append("ComboBox test module changed");
}

void ElisMainWidget::cbTopIndicatorLightChanged(int index) {
    ui->tbDisplayInfo->append("ComboBox top indicator light changed");
}

void ElisMainWidget::rbtnEnTryDirSelected() {
    ui->tbDisplayInfo->append("Radio button entry dir selected");
}

void ElisMainWidget::rbtnExitDirSelected() {
    ui->tbDisplayInfo->append("Radio button exit dir selected");
}

void ElisMainWidget::rbtnNormallyClosedSelected() {
    ui->tbDisplayInfo->append("Radio button normally clossed selected");
}

void ElisMainWidget::rbtnNormallyOpenSelected() {
    ui->tbDisplayInfo->append("Radio button normally open selected");
}

void ElisMainWidget::rbtnEntryAuthorizedSelected() {
    ui->tbDisplayInfo->append("Radio button exit authorizaed selected");
}

void ElisMainWidget::rbtnExitAuthorizedSelected() {
    ui->tbDisplayInfo->append("Radio button exit authorizaed selected");
}

void ElisMainWidget::rbtnNormalModeSelected() {
    ui->tbDisplayInfo->append("Radio button normal mode selected");
}

void ElisMainWidget::rbtnFlashModeSelected() {
    ui->tbDisplayInfo->append("Radio button flash mode selected");
}

void ElisMainWidget::cbbtnGeneralConfigurationStateChanged(int state) {
    ui->tbDisplayInfo->append("Check box general configuration state changed: state = " + QString::fromStdString(std::to_string(state)));
}

void ElisMainWidget::cbbtnAllowEntryCountStateChanged(int state) {
    ui->tbDisplayInfo->append("Check box allow entry count state changed: state = " + QString::fromStdString(std::to_string(state)));
}

void ElisMainWidget::cbbtnAllowExitCountStateChanged(int state) {
    ui->tbDisplayInfo->append("Check box allow exit count state changed: state = " + QString::fromStdString(std::to_string(state)));
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

    ui->cbComList->addItems(serialPortsNames);
    //connect(ui->cbComList, SIGNAL(currentIndexChanged(int)), this, SLOT(cbComListChanged(int)));//使用原生QComboBox,则使用currentIndexChanged信号
    connect(ui->cbComList, SIGNAL(activated(int)), this, SLOT(cbComListChanged(int)));//使用自定义CustomComboBox,则使用activated信号
}

void ElisMainWidget::setHLayoutCom(Ui::ElisMainWidget *ui) {
    ui->horizontalLayoutWidget->setStyleSheet("background:rgb(211, 211, 211)");
    ElisMainWidget::initComboBox(ui);

    ui->hLayoutCom->setSpacing(20);
    ui->btnOpenCom->setStyleSheet("background:gray");
    ui->btnOpenCom->setPalette(getButtonCommonPalette());
    connect(ui->btnOpenCom, SIGNAL(clicked()), this, SLOT(btnOpenComClicked()));

    ui->btnCloseCom->setStyleSheet("background:gray");
    ui->btnCloseCom->setPalette(getButtonCommonPalette());
    connect(ui->btnCloseCom, SIGNAL(clicked()), this, SLOT(btnCloseComClicked()));

    ui->btnCurrentStatusRequest->setStyleSheet("background:gray");
    ui->btnCurrentStatusRequest->setPalette(getButtonCommonPalette());
    connect(ui->btnCurrentStatusRequest, SIGNAL(clicked()), this, SLOT(btnCurrentStatusRequestPressed()));

    ui->btnOk->setStyleSheet("background:gray");
    ui->btnOk->setPalette(getButtonCommonPalette());
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(btnOkPressed()));
}

void ElisMainWidget::setVLayoutPassengersLeft(Ui::ElisMainWidget *ui) {
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

    connect(ui->cbbtnGeneralConfiguration, SIGNAL(stateChanged(int)), this, SLOT(cbbtnGeneralConfigurationStateChanged(int)));
}

void ElisMainWidget::setVLayoutPassengersRight(Ui::ElisMainWidget *ui) {
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
    connect(ui->btnParameterSetting, SIGNAL(clicked()), this, SLOT(btnParamterSettingPressed()));
}

void ElisMainWidget::setHLayoutPassengers(Ui::ElisMainWidget *ui) {
    ui->horizontalLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->hLayoutPassenger->setSpacing(5);
    setVLayoutPassengersLeft(ui);
    setVLayoutPassengersRight(ui);
}

void ElisMainWidget::setVLayoutModeSetting(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnGateModeSetting->setStyleSheet("background:gray");
    ui->btnGateModeSetting->setFixedSize((ui->verticalLayoutWidget_2->width() - 30), 20);
    ui->btnGateModeSetting->setPalette(getButtonCommonPalette());
    connect(ui->btnGateModeSetting, SIGNAL(clicked()), this, SLOT(btnGateModeSettingPressed()));

    ui->cbModes->addItems(ElisView::modeList);
    connect(ui->cbModes, SIGNAL(currentIndexChanged(int)), this, SLOT(cbModesChanged(int)));
    ui->vLayoutModeSetting->setContentsMargins(20, 40, 20, 0);
}

void ElisMainWidget::setVLayoutAisleMode(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_3->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnAisleModeSetting->setStyleSheet("background:gray");
    ui->btnAisleModeSetting->setFixedSize((ui->verticalLayoutWidget_6->width() - 40), 20);
    ui->btnAisleModeSetting->setPalette(getButtonCommonPalette());
    connect(ui->btnAisleModeSetting, SIGNAL(clicked()), this, SLOT(btnAisleModeSettingPressed()));

    connect(ui->rbtnNormallyClosed, SIGNAL(clicked()), this, SLOT(rbtnNormallyClosedSelected()));
    ui->rbtnNormallyClosed->setChecked(true);
    connect(ui->rbtnNormallyOpen, SIGNAL(clicked()), this, SLOT(rbtnNormallyOpenSelected()));

    ui->vLayoutAisleMode->setContentsMargins(20, 50, 20, 25);
}

void ElisMainWidget::setVLayoutTestParam(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_4->setStyleSheet("background:rgb(211, 211, 211)");
    ui->tvTestParam->setFixedSize(40, 30);
    ui->tvTestParam->setStyleSheet("background:white");

    ui->btnTestModule->setStyleSheet("background:gray");
    ui->btnTestModule->setFixedSize((ui->verticalLayoutWidget_4->width() - 30), 20);
    ui->btnTestModule->setPalette(getButtonCommonPalette());
    connect(ui->btnTestModule, SIGNAL(clicked()), this, SLOT(btnTestModulePressed()));

    ui->cbTestModule->addItems(ElisView::testsList);
    connect(ui->cbTestModule, SIGNAL(currentIndexChanged(int)), this, SLOT(cbTestModuleChanged(int)));
    ui->vLayoutTestParam->setContentsMargins(20, 20, 20, 25);
}

void ElisMainWidget::setGLayoutLightSetting(Ui::ElisMainWidget *ui) {
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
    connect(ui->btnTopIndicatorLight, SIGNAL(clicked()), this, SLOT(btnTopIndicatorLigthPressed()));

    ui->cbTopIndicatorLight->addItems(ElisView::lightsList);
    connect(ui->cbTopIndicatorLight, SIGNAL(currentIndexChanged(int)), this, SLOT(cbTopIndicatorLightChanged(int)));

    connect(ui->rbtnEntryDir, SIGNAL(clicked()), this, SLOT(rbtnEnTryDirSelected()));
    ui->rbtnEntryDir->setChecked(true);
    connect(ui->rbtnExitDir, SIGNAL(clicked()), this, SLOT(rbtnExitDirSelected()));
}

void ElisMainWidget::setPassengerAuthorization(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_5->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnPassageAuthorization->setStyleSheet("background:gray");
    ui->btnPassageAuthorization->setFixedSize((ui->verticalLayoutWidget_5->width() - 30), 20);
    ui->btnPassageAuthorization->setPalette(getButtonCommonPalette());
    connect(ui->btnPassageAuthorization, SIGNAL(clicked()), this, SLOT(btnPassageAuthorizationPressed()));

    connect(ui->rbtnEntryAuthorized, SIGNAL(clicked()), this, SLOT(rbtnEntryAuthorizedSelected()));
    ui->rbtnEntryAuthorized->setChecked(true);
    connect(ui->rbtnExitAuthorized, SIGNAL(clicked()), this, SLOT(rbtnExitAuthorizedSelected()));
    ui->vLayoutPassengerAuthorization->setContentsMargins(20, 0, 20, 15);
}

void ElisMainWidget::setGLayoutStressTest(Ui::ElisMainWidget *ui) {
    ui->gridLayoutWidget_2->setStyleSheet("background:rgb(211, 211, 211)");
    ui->gLayoutStressTest->setContentsMargins(20, 20, 20, 20);

    ui->btnStartStressTest->setStyleSheet("background:gray");
    ui->btnStartStressTest->setPalette(getButtonCommonPalette());
    connect(ui->btnStartStressTest, SIGNAL(clicked()), this, SLOT(btnStartStressTestPressed()));

    ui->btnStopStressTest->setStyleSheet("background:gray");
    ui->btnStopStressTest->setPalette(getButtonCommonPalette());
    connect(ui->btnStopStressTest, SIGNAL(clicked()), this, SLOT(btnStopStressTestPressed()));

    ui->tvStressTestIntervalTime->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvStressTestIntervalTime->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvStressTestIntervalTime->setStyleSheet("background:white");

    ui->tvEntryTotal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvEntryTotal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvEntryTotal->setStyleSheet("background:white");

    ui->tvExitTotal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvExitTotal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tvExitTotal->setStyleSheet("background:white");

    connect(ui->cbbtnAllowEntryCount, SIGNAL(stateChanged(int)), this, SLOT(cbbtnAllowEntryCountStateChanged(int)));
    connect(ui->cbbtnAllowExitCount, SIGNAL(stateChanged(int)), this, SLOT(cbbtnAllowExitCountStateChanged(int)));
}

void ElisMainWidget::setNormalFlashGedMode(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_6->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnGedMode->setStyleSheet("background:gray");
    ui->btnGedMode->setFixedSize((ui->verticalLayoutWidget_5->width() - 30), 20);
    ui->btnGedMode->setPalette(getButtonCommonPalette());
    connect(ui->btnGedMode, SIGNAL(clicked()), this, SLOT(btnGedModePressed()));

    connect(ui->rbtnNormalMode, SIGNAL(clicked()), this, SLOT(rbtnNormalModeSelected()));
    ui->rbtnNormalMode->setChecked(true);
    connect(ui->rbtnFlashMode, SIGNAL(clicked()), this, SLOT(rbtnFlashModeSelected()));
    ui->vLayoutNormalFlashGedMode->setContentsMargins(20, 0, 20, 15);
}

void ElisMainWidget::setRightButtons(Ui::ElisMainWidget *ui) {
    ui->verticalLayoutWidget_7->setStyleSheet("background:rgb(211, 211, 211)");
    ui->btnVersionRequest->setStyleSheet("background:gray");
    ui->btnVersionRequest->setPalette(getButtonCommonPalette());
    connect(ui->btnVersionRequest, SIGNAL(clicked()), this, SLOT(btnVersionRequestPressed()));

    ui->btnSetEmergency->setStyleSheet("background:gray");
    ui->btnSetEmergency->setPalette(getButtonCommonPalette());
    connect(ui->btnSetEmergency, SIGNAL(clicked()), this, SLOT(btnSetEmergencyPressed()));

    ui->btnCancelEmergency->setStyleSheet("background:gray");
    ui->btnCancelEmergency->setPalette(getButtonCommonPalette());
    connect(ui->btnCancelEmergency, SIGNAL(clicked()), this, SLOT(btnCancelEmergencyPressed()));

    ui->btnClearPassageCount->setStyleSheet("background:gray");
    ui->btnClearPassageCount->setPalette(getButtonCommonPalette());
    connect(ui->btnClearPassageCount, SIGNAL(clicked()), this, SLOT(btnClearPassageCountPressed()));

    ui->btnSensortest->setStyleSheet("background:gray");
    ui->btnSensortest->setPalette(getButtonCommonPalette());
    connect(ui->btnSensortest, SIGNAL(clicked()), this, SLOT(btnSensorTestPressed()));

    ui->btnClearInfo->setStyleSheet("background:gray");
    ui->btnClearInfo->setPalette(getButtonCommonPalette());
    connect(ui->btnClearInfo, SIGNAL(clicked()), this, SLOT(btnClearInfoPressed()));

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

