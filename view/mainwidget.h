//
// Created by chiplua on 2021/8/17.
//

#ifndef ELISRS128WINTEST_MAINWIDGET_H
#define ELISRS128WINTEST_MAINWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget {
Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);

    ~MainWidget() override;

private:
    Ui::MainWidget *ui;
};


#endif //ELISRS128WINTEST_MAINWIDGET_H
