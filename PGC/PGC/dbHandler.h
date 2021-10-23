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
    Q_INVOKABLE void Extract(QString start, QString end, QStringList books, int prod_columns, QString practice);
    QSqlDatabase db;

signals:
    void allCompleted();
    void appBookReady(QStringList list);
    void extractionCompleted();

private:
    int m_bookLength;
    int m_prodCol;
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

    unique_ptr<csvWriter> writer;

    vector<pair<QString, QString>> m_dates;
    vector<QString> m_months;
    vector<QString> m_header_months;

    vector<int> m_HoursWorked;
    vector<int> m_HoursCancelled;
    vector<int> m_NonPatientRelatedHours;
    vector<int> m_CalendarHours;
    vector<int> m_AvailableHours;
    vector<int> m_Utilisation;
    vector<int> m_NumberOfAppointments;

    int apptBookEnd();
    void setGlobals(QString start, QString end, QStringList books, int prod_columns, QString practice);
    void generateDates();
    void makeItemAnalysisTable(QString start, QString end);
    QString appendBooksToString(const char*& base, QString start_date, QString end_date);
    QString appendBooksToStringNoAppSlot(const char*& base, QString start_date, QString end_date);
    QString daysInMonth(const int& month);
    int daysInFebuary(const int& year);

    void getHoursWorked();
    void getHoursCancelled();
    void getNonPatientRelatedHours();
    void getOtherHours();
    void getUtilisation();
    void getNumberOfAppointments();


    int unbkRecall(QString PT, QString RD);
    int getUnbookedRecalls(QString start, QString end);

    int lostRecall(QString PT, QString RD);
    int getLostRecalls(QString start, QString end);

    int apptUsed(QString SKEY, int usd, int appEnd);
    int NonPatientRelatedHours(QString start, QString end);

    double getProduction(QString start, QString end);


};


