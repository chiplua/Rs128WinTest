#include <QApplication>
#include <QPushButton>
#include "view/ElisMainWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ElisMainWidget mw;
    mw.show();
    return QApplication::exec();
}
