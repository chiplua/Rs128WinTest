//
// Created by chiplua on 2021/8/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#include "mainwidget.h"
#include "ui_MainWidget.h"


MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget) {
    ui->setupUi(this);
}

MainWidget::~MainWidget() {
    delete ui;
}

