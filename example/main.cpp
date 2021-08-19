#include <QApplication>
#include <QPushButton>
#include "../src/view/ElisMainWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ElisMainWidget mw;
    mw.show();
    return QApplication::exec();
}
