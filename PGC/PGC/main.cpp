#include "PGC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PGC w;
    w.show();
    return a.exec();
}
