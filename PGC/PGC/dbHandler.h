#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QDateTime>
#include <iostream>

#include "csvWriter.h"


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
    const int m_appSlot = 5;
    int m_iconCan;
    int m_iconNS;
    int m_appStart;
    int m_appEnd;
    QString m_startDate;
    QString m_endDate;

    QString m_start_date;
    QString m_end_date;

    QStringList m_books;

    csvWriter* writer;

    vector<pair<QString, QString>> dates;
    vector<QString> m_months;

    int apptBookEnd();
    void setGlobals(QString start, QString end, QStringList books);
    void makeItemAnalysisTable(QString start, QString end);
    QString appendBooksToString(const char*& base, QString start_date, QString end_date);


    int unbkRecall(QString PT, QString RD);
    int getUnbookedRecalls(QString start, QString end);

    int lostRecall(QString PT, QString RD);
    int getLostRecalls(QString start, QString end);

    int apptUsed(QString SKEY, int usd, int appEnd);
    int getNonPatientRelatedHours(QString start, QString end);

    double getProduction(QString start, QString end);

    void generateDates();
};


