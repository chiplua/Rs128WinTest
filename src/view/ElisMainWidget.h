//
// Created by chiplua on 2021/8/18.
//

#ifndef ELISRS128WINTEST_ELISMAINWIDGET_H
#define ELISRS128WINTEST_ELISMAINWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ElisMainWidget; }
QT_END_NAMESPACE

class ElisMainWidget : public QWidget {
Q_OBJECT

public:
    explicit ElisMainWidget(QWidget *parent = nullptr);

    ~ElisMainWidget() override;

private:
    Ui::ElisMainWidget *ui;
};


#endif //ELISRS128WINTEST_ELISMAINWIDGET_H
