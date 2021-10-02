#include "PGC.h"

#include <QtWidgets/QApplication>
#include <QIcon>
#include <QDebug>

#include <iostream>
#include <filesystem>

#include "QtPassword.h"

using namespace std;
using namespace filesystem;

QString workingDirectory;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    workingDirectory = QString::fromWCharArray( weakly_canonical(path(argv[0])).parent_path().c_str() );
    qDebug() << workingDirectory;
    app.setWindowIcon(QIcon(workingDirectory + "\\centaur-icon.png"));

    PGC w;

    QFont font("Calibri", 10);
    int buttonHeight = 24;

    QtPassword qp(font, buttonHeight);

    QObject::connect(&qp, SIGNAL(passwordAccepted()), &w, SLOT(show()));
    QObject::connect(&qp, SIGNAL(passwordRejected()), &app, SLOT(quit()));

    qp.show();

    return app.exec();
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



