//
// Created by chiplua on 2021/8/24.
//

#ifndef ELISRS128WINTEST_ELISSENSORTESTWIDGET_H
#define ELISRS128WINTEST_ELISSENSORTESTWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ElisSensorTestWidget; }
QT_END_NAMESPACE

class ElisSensorTestWidget : public QWidget {
Q_OBJECT

public:
    explicit ElisSensorTestWidget(QWidget *parent = nullptr);

    ~ElisSensorTestWidget() override;

private:
    Ui::ElisSensorTestWidget *ui;
};


#endif //ELISRS128WINTEST_ELISSENSORTESTWIDGET_H
