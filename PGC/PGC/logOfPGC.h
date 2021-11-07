#pragma once
#include <QObject>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <errno.h>
#include <QAbstractButton>
#include <QPushButton>
//#include <unistd.h>

using namespace std;

class  logOfPGC : public QObject
{
    Q_OBJECT
public:
    unique_ptr<ofstream> log_ptr;

    ofstream log;

    explicit logOfPGC(QObject* parent = nullptr) : QObject(parent) { log_ptr = make_unique<ofstream>(); };
    ~logOfPGC() { log_ptr->close(); log.close(); };

    QString file_name;

public slots:
    void openLog();

signals:
    void noLogFileOpended();
    void logFileOpened();

public:
        ofstream& getOFStream() { return log; };

public slots:
        void appendString(QString str);
};