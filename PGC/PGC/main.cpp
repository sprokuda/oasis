#include "PGC.h"

#include <QtWidgets/QApplication>
#include <QIcon>
#include <QDebug>

#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

extern QString workingDirectory;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    workingDirectory = QString::fromWCharArray( weakly_canonical(path(argv[0])).parent_path().c_str() );
    qDebug() << workingDirectory;
    a.setWindowIcon(QIcon(workingDirectory + "\\centaur-icon.png"));

    PGC w;
    w.show();

    return a.exec();
}

/*

{
    QIcon icon;

    QIcon::Mode mode = QIcon::Normal;
    QIcon::State state = QIcon::On;

    const QString fileName = "./centaur-logo.png";
    QImage image(fileName);
    if (!image.isNull())
        icon.addPixmap(QPixmap::fromImage(image), mode, state);


*/



