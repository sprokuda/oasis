#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <iostream>
#include <vector>
//#include "dbScripts.h"

class dbHandler : public QObject
{
    Q_OBJECT
public:
    explicit dbHandler(QObject* parent = nullptr);
    ~dbHandler();

    Q_INVOKABLE void doQueries();
    Q_INVOKABLE void queryAppBook();
    Q_INVOKABLE void loadBooksAndFunctions();
    Q_INVOKABLE void Extract(QString start, QString end, QStringList books);
    QSqlDatabase db;

signals:
    void allCompleted();
    void appBookReady(QStringList list);
    void extractionCompleted();

private:
    const int appSlot = 5;
    int iconCan;
    int iconNS;
    int appStart;
    int appEnd;
    QString startDate;
    QString endDate;

    QString start_date;
    QString end_date;

    int apptBookEnd();
    void setGlobals(QString start, QString end);
    void makeItemAnalysisTable(QString start, QString end);


    int unbkRecall(QString PT, QString RD);
    int getUnbookedRecalls(QString start, QString end);
};

