#include<windows.h>
#include <iomanip>
#include "dbHandler.h"
#include "dbScripts.h"
#include<QMetaType>


using namespace std;

void log_query_result(const QString& header, const QString& msg)
{
    if (msg.isEmpty()) cout << header.toStdString() << ": " << "no error" << "\n";
    else cout << header.toStdString() << ": " << "last error: " << msg.toStdString() << "\n";
}


dbHandler::dbHandler(QObject* parent) : QObject(parent)
{

}

dbHandler::~dbHandler()
{
    QSqlQuery query(db);
#if 1
    query.exec(dlt_tbl_FIRST_INV_721);
    query.exec(dlt_tbl_LAST_INV_722);
    query.exec(dlt_tbl_FUT_APP_723);
    query.exec(dlt_tbl_APP_BOOK_724);
    query.exec(dlt_tbl_ITEMS_725);
//    query.exec(dlt_tbl_ITEM_ANALYSIS_726);
    query.exec(dlt_tbl_CHURN_727);

#endif
    query.exec(dlt_tbl_ITEM_ANALYSIS_726);
}

void dbHandler::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC", "mydb");
    db.setDatabaseName("OASIS");//"DRIVER={MIMER};DSN='OASIS';DATABASE=OASIS")
    db.setUserName("sysadm");
    db.setPassword("12345pass");
#if 1
    if (!db.open())
    {
        log_query_result("", db.lastError().text());

        emit dbConnectError(db.lastError().text());
        return;
    }
#endif
//    Sleep(300);
    emit dbConnectSuccessful();
}


void dbHandler::loadBooksAndFunctions()
{
    QDateTime time(QDate::currentDate());
    auto start_time = time.currentMSecsSinceEpoch();

    QSqlQuery query(db);

#if 1

    query.exec(crt_tbl_FIRST_INV_721);
    query.exec(ppl_tbl_FIRST_INV_721);
    log_query_result("FIRST_INV", db.lastError().text());

    query.exec(crt_tbl_LAST_INV_722);
    query.exec(ppl_tbl_LAST_INV_722);
    log_query_result("LAST_INV", db.lastError().text());

    query.exec(crt_tbl_FUT_APP_723);
    query.exec(ppl_tbl_FUT_APP_723);
    log_query_result("FUT_APP", db.lastError().text());

    query.exec(crt_tbl_APP_BOOK_724);
    query.exec(ppl_tbl_APP_BOOK_724);
    log_query_result("APP_BOOK", db.lastError().text());

    query.exec(crt_tbl_ITEMS_725);
    query.exec(ppl_tbl_ITEMS_725);
    log_query_result("ITEMS", db.lastError().text());

    query.exec(crt_tbl_CHURN_727);
    query.exec(ppl_tbl_CHURN_727_1);
    query.exec(ppl_tbl_CHURN_727_2);
    query.exec(ppl_tbl_CHURN_727_3);
    query.exec(ppl_tbl_CHURN_727_4);
    query.exec(ppl_tbl_CHURN_727_5);
    log_query_result("CHURN", db.lastError().text());

#endif

    queryAppBook();
    cout << "Time taken to create tables: " << time.currentMSecsSinceEpoch() - start_time << "msec."  << endl;
}

void dbHandler::queryAppBook()
{
    QSqlQuery query(db);

    auto padded = [](string inp) 
    { 
        int size = inp.size();
        switch (size)
        {
        case 1: return "000" + inp; break;
        case 2: return "00" + inp; break;
        case 3: return "0" + inp;  break;
        case 4: return inp;  break;
        default: return string("0000");
        }
    };

    const char* script = "SELECT BOOKNO, BOOKNAME from APP_BOOK;";
    map<string, string> local_books = { {"BOOK 0001",padded("1")},{"BOOK 0002",padded("02")},{"BOOK 0005",padded("005")}, {"BOOK 0006",padded("0006")} };

    query.exec(script);
//    cout << "Execution of query : "<< "\"" << script << "\"" << " last error: "<< db.lastError().text().toStdString() << "\n";
 //   fflush(stdout);
    m_books_map.clear();
    while (query.next())
    {

        m_books_map.emplace(query.value(1).toString().left(9).toStdString(),padded(query.value(0).toString().toStdString()));
    }
    log_query_result("BOOKS", db.lastError().text());

    qRegisterMetaType<std::map<std::string, std::string>>("std::map<std::string, std::string>");
    qRegisterMetaType<map<string, string>>("map<string, string>");
    emit appBookReady(m_books_map);
}

void dbHandler::Extract(QString start, QString end, QStringList books, int prod_columns, QString practice)
{
    writer = make_unique<csvWriter>();
    QSqlQuery query(db);

    QDate current_date = QDate::currentDate();
    QTime current_time = QTime::currentTime();

    QDateTime time(QDate::currentDate());
    auto start_time = time.currentMSecsSinceEpoch();

    setGlobals(start, end, books, prod_columns, practice);
    makeItemAnalysisTable(start, end);
#if 1
    getHoursWorked();
    getHoursCancelled();
    getNonPatientRelatedHours();
    getOtherHours();
    getUtilisation();
    getNumberOfAppointments();
    getAllAndActivePatients();
    getNewPatients();
    getChurnedPatients();
    getUniquePatients();
    getLapsedPatients();
    getNewPatientPercent();
    getNetPatientGain();

    getUnbookedRecalls();
    getTotalRecalls();
    getRecallEffectiveness();
    getLostRecalls();

    getTotalIncompleteTreatmentValue();
    getTreatmentPlansCreated();
    getTreatmentPlansNotAccepted();
    getTreatmentPlanConversionRate();

    getProduction();
    getProductionPerValue("Production Per Available Hour", m_AvailableHours);
    getProductionPerValue("Production Per Working Hour", m_HoursWorked);
    getProductionPerValue("Production Per Patient", m_UniquePatients);
    getProductionPerValue("Production Per Appointment", m_NumberOfAppointments);

    getProductionThroughLost("Lost Revenue Through Cancellations", m_HoursWorked, m_HoursCancelled);
    getProductionThroughLost("Lost Revenue Through Patient Churn", m_UniquePatients, m_ChurnedPatients);
    getDebtors();
    getTop10Items("Top 10 Items by Value", QString(query_Top_10_Items_By_Value_7433), "$");
    getTop10Items("Top 10 Items by Count", QString(query_Top_10_Items_By_Count_7434));
    writeGlobals(current_date, current_time);

#endif

    cout << "Time taken to extract data: " << time.currentMSecsSinceEpoch() - start_time << "msec." << endl;
    emit extractionCompleted();
}


int dbHandler::apptBookEnd()
{
    const char* crt_st = "SELECT CAST(F1 AS INTEGER) FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    const char* crt_hrs = "SELECT CAST(F2 AS INTEGER) FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000'";

    QSqlQuery query(db);

    query.exec(crt_st);
    query.next();
    int st = query.value(0).toInt();

    query.exec(crt_hrs);
    query.next();
    int hrs = query.value(0).toInt();

    return st + hrs + 1;
}

void dbHandler::makeItemAnalysisTable(QString start, QString end)
{
    QSqlQuery query(db);
    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg(start).arg(end);

    query.exec(crt_tbl_ITEM_ANALYSIS_726);
//    cout << db.lastError().text().toStdString() << endl;

    query.exec(string_726.toStdString().c_str());
//    cout << db.lastError().text().toStdString() << endl;

    query.exec("SELECT * FROM ITEM_ANALYSIS;");

    //while (query.next())
    //{
    //        cout << query.value(0).toString().toStdString() << "\t";
    //        cout << query.value(1).toString().toStdString() << "\t ";
    //        cout << query.value(2).toString().toStdString() << "\n";
    //        fflush(stdout);
    //}
    log_query_result("ItemAnalysis", db.lastError().text());
}

void dbHandler::setGlobals(QString start, QString end, QStringList books, int prod_columns, QString practice)
{
    m_iconCan = 111;
    m_iconNS = 222;
    m_appStart = 22;
    m_appEnd = 33;
    this->m_books = books;

    cout << "the books are: " << m_books.join(";").toStdString() << "\n";

    QSqlQuery query(db);

    m_start_date = start;
    m_end_date = end;

    m_startDate = start.remove("-");
    m_endDate = end.remove("-");

    generateDates();

    m_practice = practice;
    
    const char* glb_bookLength = "SELECT CAST(F2 AS INTEGER) +1 AS appbooklength FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    query.exec(glb_bookLength);
    query.next();
    m_bookLength = query.value(0).toInt();
    cout << "$bookLength = " << m_bookLength << endl;

    m_prodCol = prod_columns;
    cout << "$prodCol = " << m_prodCol << endl;

    cout << "$appSlot = " << m_appSlot << endl;

    const char* glb_iconCan = "Select CAST(F5 AS INTEGER)  as CAN from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE' ; ";
    query.exec(glb_iconCan);
    query.next();
    m_iconCan = query.value(0).toInt();
    cout << "$iconCan = " << m_iconCan << endl;

    const char* glb_iconNS = "Select CAST(F6 AS INTEGER)  as NS from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE'; ";
    query.exec(glb_iconNS);
    query.next();
    m_iconNS = query.value(0).toInt();
    cout << "$iconNS = " << m_iconNS << endl;

    const char* glb_appStart = "SELECT CAST(F1 AS INTEGER) as appStart FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    query.exec(glb_appStart);
    query.next();
    m_appStart = query.value(0).toInt();
    cout << "$appStart = " << m_appStart << endl;

    m_appEnd = apptBookEnd();
    cout << "$appEnd = " << m_appEnd << endl;
}


QString dbHandler::appendBooksToString(const char*& base, QString start_date, QString end_date)
{
        QString str= QString(base).arg(m_appSlot).arg(m_iconCan).arg(m_iconNS).arg(start_date).arg(end_date).arg(m_appStart - 1);
    for (int i = 0; i < m_books.size(); i++)
    {
        if(i == 0) str.append("(");

        if (i < m_books.size() - 1)
            str.append(QString(append_book).arg(m_books.at(i)));
        else
        {
            str.append(QString(append_book).arg(m_books.at(i)).remove(QString("OR")));
            str.append(");");
        }
    }
    return str;
}

QString dbHandler::appendBooksToStringNoAppSlot(const char*& base, QString start_date, QString end_date)
{
    QString str = QString(base).arg("").arg(m_iconCan).arg(m_iconNS).arg(start_date).arg(end_date).arg(m_appStart - 1);
    for (int i = 0; i < m_books.size(); i++)
    {
        if (i == 0) str.append("(");

        if (i < m_books.size() - 1)
            str.append(QString(append_book).arg(m_books.at(i)));
        else
        {
            str.append(QString(append_book).arg(m_books.at(i)).remove(QString("OR")));
            str.append(");");
        }
    }
    return str;
}

int dbHandler::unbkRecall(QString PT, QString RD)
{
    QSqlQuery query(db);
    const char* script = "SELECT  count(SKEY)  from paapplns where patnumber = '%1' and entrydate between date'%2' and date'%3' + INTERVAL'30'DAY;";
    QString str =  QString(script).arg(PT).arg(RD).arg(RD);

    query.exec(str.toStdString().c_str());
    query.next();
 //   cout << query.value(0).toString().toStdString() << endl;
    int app = query.value(0).toInt();
    int unbooked;
    if (app > 0) unbooked = 0;
    else unbooked = 1;

    return unbooked;
    
//@ 
//CREATE FUNCTION unbkRecall(PT VARCHAR(6), RD DATE) RETURNS INTEGER
//READS SQL DATA
//BEGIN
//DECLARE unbooked INTEGER;
//DECLARE app INTEGER;
//SELECT  count(SKEY)  INTO app  from paapplns where patnumber = PT and entrydate between RD and RD + INTERVAL'30'DAY;
//IF app > 0 then
//SET unbooked = 0;
//ELSE SET unbooked = 1;
//END IF;
//RETURN(Unbooked);
//END
//@
}

int dbHandler::UnbookedRecalls(QString start, QString end)
{
    int result = 0;
    QSqlQuery query(db);
    QString str = QString("Select * from ptpatnts where details like 'Recall%'  and datecreated between date'%1' and date'%2';").arg(start).arg(end);

    query.exec(str.toStdString().c_str());
    while (query.next())
    {
        QString patnumber = query.value(0).toString();
        QString datecreated = query.value(4).toString();
        result += unbkRecall(patnumber, datecreated);
    }
    log_query_result("Unbooked Recalls for interval: " + start + "/" + end, db.lastError().text());
    return result;
}


int dbHandler::lostRecall(QString PT, QString RD)
{
    QSqlQuery query(db);
    const char* script = "SELECT  count(SKEY)  from paapplns where patnumber = '%1' and entrydate > date'%2' - INTERVAL'1'DAY";
    QString str = QString(script).arg(PT).arg(RD);

    query.exec(str.toStdString().c_str());
    query.next();
    int app = query.value(0).toInt();
    int lost;
    if (app > 0) lost = 0;
    else lost = 1;

    return lost;

//@ 
//CREATE FUNCTION lostRecall(PT VARCHAR(6), RD DATE) RETURNS INTEGER
//READS SQL DATA
//BEGIN
//DECLARE lost INTEGER;
//DECLARE app INTEGER;
//SELECT  count(SKEY)  INTO app  from paapplns where patnumber = PT and entrydate > RD - INTERVAL'1'DAY;
//IF app > 0 then
//SET lost = 0;
//ELSE SET lost = 1;
//END IF;
//RETURN(lost);
//END
//@
}

int dbHandler::LostRecalls(QString start, QString end)
{
    int result = 0;
    QSqlQuery query(db);
    QString str = QString("Select * from ptpatnts where details like 'Recall%'  and datecreated between date'%1' and date'%2';").arg(start).arg(end);

    query.exec(str.toStdString().c_str());
    while (query.next())
    {
        QString patnumber = query.value(0).toString();
        QString datecreated = query.value(4).toString();
        result += lostRecall(patnumber, datecreated);
    }
    log_query_result("Lost Recalls for interval: " + start + "/" + end, db.lastError().text());
    return result;
}


int dbHandler::apptUsed(QString SKEY, int usd, int appEnd)
{
    bool ok;
    int stHr = QString(QString(SKEY.at(16)) + QString(SKEY.at(17))).toInt(&ok);
//    cout << stHr << endl;
    int maxDur = (appEnd - stHr) * 60;
    int usedTime = 0;
    if (usd > maxDur) usedTime = maxDur;
    else usedTime = usd;

    return usedTime;

    //@ 
    //    CREATE FUNCTION apptUsed(SKEY VARCHAR(20), usd INTEGER, appEnd INTEGER) RETURNS INTEGER
    //    READS SQL DATA
    //    BEGIN
    //    DECLARE stHr INTEGER;
    //DECLARE maxDur INTEGER;
    //DECLARE usedTime INTEGER;

    //SET stHr = CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER);
    //SET maxDur = (appEnd - StHr) * 60;
    //IF usd > maxDur then
    //    SET usedTime = maxDur;
    //ELSE SET usedTime = usd;
    //END IF;
    //RETURN(usedTime);
    //END
    //    @
}


int dbHandler::NonPatientRelatedHours(QString start, QString end)
{
    const char* base = "Select * from paapplns where  SKEY BETWEEN '%1%' AND '%2%' and (patnumber = '000000' or patnumber = '') AND CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER) > %3 AND ";
    QString str = QString(base).arg(start).arg(end).arg(m_appStart - 1);
    for (int i = 0; i < m_books.size(); i++)
    {
        if (i == 0) str.append("(");

        if (i < m_books.size() - 1)
            str.append(QString(append_book).arg(m_books.at(i)));
        else
        {
            str.append(QString(append_book).arg(m_books.at(i)).remove(QString("OR")));
            str.append(");");
        }
    }

    QSqlQuery query(db);
    int result = 0;

    query.exec(str.toStdString().c_str());
    while (query.next())
    {
        QString SKEY = query.value(0).toString();
        int timeused = query.value(17).toInt();

        result += apptUsed(SKEY, timeused * m_appSlot, m_appEnd);// "21" is hardcoded instead of value of m_appEnd
    }
    log_query_result("Non Patient Related Hours for interval: " + start + "/" + end, db.lastError().text());
    return result/60;
}

void dbHandler::doQueries()
{
    const char* script = "SELECT * FROM pbpatmas;";
    QStringList list;
    QSqlQuery query(db);

    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg("001").arg("002");

//    query.exec(script);
//    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    while (query.next())
    {
        cout << query.value(0).toString().toStdString() << " ";
        cout << query.value(1).toString().toStdString() << " ";
        cout << query.value(2).toString().toStdString() << "\n";
    }
    cout << db.lastError().text().toStdString() << endl;

	//std::cout << "test\n";
 //   fflush(stdout);
	Sleep(3000);
	emit allCompleted();
}

