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

void log_query_result(const QString& header, const QString& msg);


class dbHandler : public QObject
{
    Q_OBJECT
public:
    explicit dbHandler(QObject* parent = nullptr);
    ~dbHandler();

    Q_INVOKABLE void connectDatabase();
    Q_INVOKABLE void loadBooksAndFunctions();
    Q_INVOKABLE void queryAppBook();
    Q_INVOKABLE void Extract(QString start, QString end, QStringList books, int prod_columns, QString practice);
    QSqlDatabase db;

    Q_INVOKABLE void doQueries();

signals:

    void dbConnectError(QString message);
    void dbConnectSuccessful();
    void allCompleted();
    void appBookReady(map<string,string> books);
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
    QString m_practice;
    QStringList m_books;
    map<string, string> m_books_map;

    unique_ptr<csvWriter> writer;

    vector<pair<QString, QString>> m_dates;
    vector<QString> m_months;
    vector<QString> m_header_months;

    QDate current_date;
    QTime current_time;

    vector<int> m_HoursWorked;
    vector<int> m_HoursCancelled;
    vector<int> m_NonPatientRelatedHours;
    vector<int> m_CalendarHours;
    vector<int> m_AvailableHours;
    vector<int> m_Utilisation;
    vector<int> m_NumberOfAppointments;
    vector<int> m_NewPatients;
    vector<int> m_ChurnedPatients;
    vector<int> m_UniquePatients;
    vector<int> m_NewPatientPercent;
    vector<int> m_NetPatientGain;
    vector<int> m_UnbookedRecalls;
    vector<int> m_TotalRecalls;
    vector<int> m_RecallEffectiveness;
    vector<int> m_LostRecalls;
    vector<int> m_TreatmentPlansCreated;
    vector<int> m_TreatmentPlansNotAccepted;
    vector<int> m_TreatmentPlanConversionRate;
    vector<int> m_Production;

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
    void getAllAndActivePatients();
    void getNewPatients();
    void getChurnedPatients();
    void getUniquePatients();
    void getLapsedPatients();
    void getNewPatientPercent();
    void getNetPatientGain();
    void getUnbookedRecalls();
    void getTotalRecalls();
    void getRecallEffectiveness();
    void getLostRecalls();
    void getTotalIncompleteTreatmentValue();
    void getTreatmentPlansCreated();
    void getTreatmentPlansNotAccepted();
    void getTreatmentPlanConversionRate();
    void getProduction();
    void getProductionPerValue(const QString& header, const vector<int>& hours);
    void getProductionThroughLost(const QString& header, const vector<int>& hours, const vector<int>& lost);
    void getDebtors();
    void getTop10Items(const QString& header, const QString& str, const QString prefix = "");
    void writeGlobals(const QDate& current_date, const QTime& current_time);

        
    int unbkRecall(QString PT, QString RD);
    int UnbookedRecalls(QString start, QString end);

    int lostRecall(QString PT, QString RD);
    int LostRecalls(QString start, QString end);

    int apptUsed(QString SKEY, int usd, int appEnd);
    int NonPatientRelatedHours(QString start, QString end);

    double Production(QString start, QString end);


};


