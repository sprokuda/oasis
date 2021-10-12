#include "PGC.h"

#include <QtWidgets/QApplication>
#include <QIcon>
#include <QDebug>

#include <iostream>
#include <filesystem>

#include "ThreadLogStream.h"
#include "QtPassword.h"

using namespace std;
using namespace filesystem;

QString workingDirectory;

QFont workingFont;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ThreadLogStream qout(std::cout);

    workingFont = QFont("Calibri", 10);

    workingDirectory = QString::fromWCharArray( weakly_canonical(path(argv[0])).parent_path().c_str() );
    qDebug() << workingDirectory;
    app.setWindowIcon(QIcon(workingDirectory + "\\centaur-icon.png"));

    PGC w;
    QObject::connect(&qout, SIGNAL(sendLogString(QString)), &w, SLOT(updateLog(QString)));
    w.show();
    w.initialLoad();
    //QFont font("Calibri", 10);
    //int buttonHeight = 24;
    //QtPassword qp(font, buttonHeight);

    //QObject::connect(&qp, SIGNAL(passwordAccepted()), &w, SLOT(show()));
    //QObject::connect(&qp, SIGNAL(passwordRejected()), &app, SLOT(quit()));

    //qp.show();

    return app.exec();
}



