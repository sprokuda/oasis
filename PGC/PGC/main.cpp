#include "PGC.h"

#include <QtWidgets/QApplication>
#include <QIcon>
#include <QDebug>
#include <QTime>
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
        cout << "QtDebugMsg: " << msg.toStdString() << "\n";
        //qDebug() << "QtDebugMsg: " << msg << "\n";
        break;
    case QtInfoMsg:
        cout << "QtInfoMsg: " << msg.toStdString() << "\n";
        break;
    case QtWarningMsg:
        cout << "QtWarningMsg: " << msg.toStdString() << "\n";
        break;
    case QtCriticalMsg:
        cout << "QtCriticalMsg: " << msg.toStdString() << "\n";
        break;
    case QtFatalMsg:
        cout << "QtFatalMsg: " << msg.toStdString() << "\n";
        fprintf(stdout, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}


QString initial_log;

int main(int argc, char *argv[])
{
    ThreadLogStream qout(cout);
    qInstallMessageHandler(MessageOutput);
    QApplication app(argc, argv);
    QString workingDirectory = QString::fromWCharArray(weakly_canonical(path(argv[0])).parent_path().c_str());

    app.setWindowIcon(QIcon(":PGC/resources/centaur-icon.png"));

    QFont workingFont = QFont("Calibri", 10);

    QtPassword qp(workingFont);
    qp.show();

    logOfPGC log_of_pgc;
    PGC w;

    QObject::connect(&qp, SIGNAL(passwordAccepted()), &log_of_pgc, SLOT(openLog()));
    QObject::connect(&qp, SIGNAL(passwordRejected()), &app, SLOT(quit()));
    QObject::connect(&log_of_pgc, SIGNAL(noLogFileOpended()), &app, SLOT(quit()));
    QObject::connect(&log_of_pgc, &logOfPGC::logFileOpened, [&qout, &log_of_pgc, &w, &workingDirectory]() 
        {
            QObject::connect(&qout, SIGNAL(sendLogString(QString)), &log_of_pgc, SLOT(appendString(QString)));
            QObject::connect(&qout, SIGNAL(sendLogString(QString)), &w, SLOT(updateLog(QString)));
            cout << "Started at: " 
                << QDate::currentDate().toString("yyyy/MM/dd").toStdString() << " "
                << QTime::currentTime().toString("hh:mm:ss").toStdString()
                << "\n";
            cout << initial_log.toStdString();
            cout << "PGC.exe is run from : " << workingDirectory.toStdString() << "\n";
            w.show();
            w.initialLoad();
        });

    return app.exec();
}



