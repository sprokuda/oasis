#include "PGC.h"

#include <QtWidgets/QApplication>
#include <QIcon>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <filesystem>

#include "ThreadLogStream.h"
#include "logOfPGC.h"
#include "QtPassword.h"

using namespace std;
using namespace filesystem;


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
        fprintf(stdout, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}




int main(int argc, char *argv[])
{
    ThreadLogStream qout(cout);
    qInstallMessageHandler(MessageOutput);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":PGC/resources/centaur-icon.png"));

    QFont workingFont = QFont("Calibri", 10);

    QtPassword qp(workingFont);
    qp.show();

    logOfPGC log_of_pgc;
    PGC w;

    QObject::connect(&qp, SIGNAL(passwordAccepted()), &log_of_pgc, SLOT(openLog()));
    QObject::connect(&qp, SIGNAL(passwordRejected()), &app, SLOT(quit()));
    QObject::connect(&log_of_pgc, SIGNAL(noLogFileOpened()), &app, SLOT(quit()));
    QObject::connect(&log_of_pgc, &logOfPGC::logFileOpened, [&qout, &log_of_pgc, &w]() 
        {
            QObject::connect(&qout, SIGNAL(sendLogString(QString)), &log_of_pgc, SLOT(appendString(QString)));
            w.show();
            QObject::connect(&qout, SIGNAL(sendLogString(QString)), &w, SLOT(updateLog(QString)));
            w.initialLoad();
        });

    QString workingDirectory = QString::fromWCharArray( weakly_canonical(path(argv[0])).parent_path().c_str() );
    qDebug() << workingDirectory;

    return app.exec();
}



