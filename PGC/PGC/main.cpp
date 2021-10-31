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
        fprintf(stdout, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}


void CreateLogFile()
{
    const char* dir1 = "OASIS";
    const char* dir2 = "PGC";

    QDir dir;
    dir.cd("C:/");

    if (!QDir(dir1).exists())
        cout << "QDir returned: " << dir.mkdir(dir1) << endl;
    dir.cd(dir1);

    const QFileInfo outputDir1(dir.absolutePath().toStdString().c_str());
    if ((!outputDir1.exists()) || (!outputDir1.isDir()) || (!outputDir1.isWritable()))
    {
        cout << "output directory does not exist, is not a directory, or is not writeable"
            << "\t" << outputDir1.absoluteFilePath().toStdString() << endl;
    }

    if (!QDir(dir2).exists())
        cout << "QDir returned: " << dir.mkdir(dir2) << endl;
    dir.cd(dir2);

    const QFileInfo outputDir2(dir.absolutePath().toStdString().c_str());
    if ((!outputDir2.exists()) || (!outputDir2.isDir()) || (!outputDir2.isWritable()))
    {
        cout << "output directory does not exist, is not a directory, or is not writeable"
            << "\t" << outputDir2.absoluteFilePath().toStdString() << endl;
    }

    QString fileName = QDate::currentDate().toString("yyyyMMdd") + "__" + QTime::currentTime().toString("hh-mm-ss-zzz") + QString(".log");
    cout << (dir.absolutePath() + "\\" + fileName).toStdString() << endl;
    fflush(stdout);

    QFile file = QFile(dir.absolutePath() + "\\" + fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.close();
    }
}





int main(int argc, char *argv[])
{
    ThreadLogStream qout(cout);
    qInstallMessageHandler(MessageOutput);
    QApplication app(argc, argv);

    logOfPGC log;
    log.openLog("example.log");

tryOpenLog:
    if(!log.isOpened())
    {
        QMessageBox msgBox(nullptr);
        msgBox.setText("Log file can not be created");
        msgBox.setIcon(QMessageBox::Warning);
        auto* open = msgBox.addButton("Try to open again", QMessageBox::ActionRole);
        auto* exit = msgBox.addButton("Exit Program", QMessageBox::ActionRole);

        msgBox.exec();

        if (msgBox.clickedButton() == open)
        {
            log.openLog("example.log"); goto tryOpenLog;
        }
        else if (msgBox.clickedButton() == exit)
        {
            return 0;
        }
    }


    

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



