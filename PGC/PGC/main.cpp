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

void MessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        cout << "QtDebugMsg: " << msg.toStdString() << endl;
        break;
    case QtInfoMsg:
        cout << "QtInfoMsg: " << msg.toStdString() << endl;
        break;
    case QtWarningMsg:
        cout << "QtWarningMsg: " << msg.toStdString() << endl;
        break;
    case QtCriticalMsg:
        cout << "QtCriticalMsg: " << msg.toStdString() << endl;
        break;
    case QtFatalMsg:
        cout << "QtFatalMsg: " << msg.toStdString() << endl;
//        fprintf(stdout, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
//        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(MessageOutput);
    QApplication app(argc, argv);

    workingFont = QFont("Calibri", 10);

    workingDirectory = QString::fromWCharArray( weakly_canonical(path(argv[0])).parent_path().c_str() );
    qDebug() << workingDirectory;
    app.setWindowIcon(QIcon(workingDirectory + "\\centaur-icon.png"));

    PGC w;
    ThreadLogStream qout(cout);
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



