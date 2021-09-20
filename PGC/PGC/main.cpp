#include "PGC.h"

#include <QtWidgets/QApplication>
#include <QIcon>
#include <QDebug>

#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString workingDirectory = QString::fromWCharArray( weakly_canonical(path(argv[0])).parent_path().c_str() );
    a.setWindowIcon(QIcon(workingDirectory + "\\centaur-icon.png"));

    PGC w;
    w.show();

    return a.exec();
}
