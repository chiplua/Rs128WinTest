#include <QApplication>
#include <QPushButton>
#include "view/MainWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWidget mw;
    mw.show();
    return QApplication::exec();
}
