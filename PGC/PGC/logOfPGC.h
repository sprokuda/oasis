#pragma once
#include <QObject>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDateTime>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

class  logOfPGC : public QObject
{
    Q_OBJECT
public:
    unique_ptr<ofstream> log_ptr;

    ofstream log;

    explicit logOfPGC(QObject* parent = nullptr) : QObject(parent) { log_ptr = make_unique<ofstream>(); };
    //    explicit logOfPGC() { log_ptr = make_unique<ofstream>(); };
    ~logOfPGC() { log_ptr->close(); log.close(); };

        void openLog(string file_name) 
        { 
            const char* dir_name = "C:/OASIS/PGC/log";

            QDir dir;
            if (!QDir(dir_name).exists()) dir.mkdir(dir_name);
            dir.cd(dir_name);

            const QFileInfo outputDir2(dir.absolutePath());
            if ((!outputDir2.exists()) || (!outputDir2.isDir()) || (!outputDir2.isWritable()))
            {
                QMessageBox::warning(nullptr, 0, "Output directory problem","output directory does not exist,\nis not a directory,\nor is not writeable");
                return;
            }
            QString fileName = dir.absolutePath() + "\\" + QDate::currentDate().toString("yyyyMMdd") + "_" + QTime::currentTime().toString("hh-mm-ss-zzz") + QString(".log");
            log.open(fileName.toStdString());
        };

        ofstream& getOFStream() { return log; };
        bool isOpened() { return log.is_open(); };
        void appendString(QString str) { log << str.toStdString(); };
};