#include<windows.h>
#include <iomanip>
#include "dbHandler.h"
#include "dbScripts.h"



using namespace std;

//extern const char* crt_tbl_FIRST_INV_721;

dbHandler::dbHandler(QObject* parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QODBC", "mydb");
    db.setDatabaseName("OASIS");//"DRIVER={MIMER};DSN='OASIS';DATABASE=OASIS")
    db.setUserName("sysadm");
    db.setPassword("12345pass");

    if (!db.open())
    {
        cout << "error:\n";
        cout << db.lastError().text().toStdString() << endl;
        fflush(stdout);
    }

}

dbHandler::~dbHandler()
{
    QSqlQuery query(db);
#if 0
    query.exec(dlt_tbl_FIRST_INV_721);
    query.exec(dlt_tbl_LAST_INV_722);
    query.exec(dlt_tbl_FUT_APP_723);
    query.exec(dlt_tbl_APP_BOOK_724);
    query.exec(dlt_tbl_ITEMS_725);
    query.exec(dlt_tbl_ITEM_ANALYSIS_726);
    query.exec(dlt_tbl_CHURN_727);
    query.exec(dlt_tbl_Production_728);
    query.exec(dlt_fncn_unbkRecall_729);
    query.exec(dlt_fncn_lostRecall_7210);
    query.exec(dlt_fncn_apptbookEnd_7211);
    query.exec(dlt_fncn_apptUsed_7212);
    query.exec(dlt_prcd_Production_7213);
#endif
}


void dbHandler::loadBooksAndFunctions()
{
    QSqlQuery query(db);

#if 0

    query.exec(crt_tbl_FIRST_INV_721);
    query.exec(ppl_tbl_FIRST_INV_721);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_tbl_LAST_INV_722);
    query.exec(ppl_tbl_LAST_INV_722);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_tbl_FUT_APP_723);
    query.exec(ppl_tbl_FUT_APP_723);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_tbl_APP_BOOK_724);
    query.exec(ppl_tbl_APP_BOOK_724);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_tbl_ITEMS_725);
    query.exec(ppl_tbl_ITEMS_725);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_tbl_ITEM_ANALYSIS_726);
    query.exec(ppl_tbl_ITEM_ANALYSIS_726);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_tbl_CHURN_727);
    query.exec(ppl_tbl_CHURN_727_1);
    query.exec(ppl_tbl_CHURN_727_2);
    query.exec(ppl_tbl_CHURN_727_3);
    query.exec(ppl_tbl_CHURN_727_4);
    query.exec(ppl_tbl_CHURN_727_5);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_fncn_unbkRecall_729);
    query.next();
    cout << query.value(0).toString().toStdString() << endl;
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

//    cout << crt_fncn_unbkRecall_729 << endl;
//    fflush(stdout);


    query.exec(crt_fncn_lostRecall_7210);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_fncn_apptbookEnd_7211);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_fncn_apptUsed_7212);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec(crt_prcd_Production_7213);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

#endif

    queryAppBook();
}

void dbHandler::queryAppBook()
{
    QSqlQuery query(db);

    const char* script = "SELECT * FROM APP_BOOK;";
    QStringList list;// = { "0022","0021","0023" };

    query.exec(script);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    while (query.next())
    {
        //cout << query.value(0).toString().toStdString();
        list << query.value(0).toString();
    }
    cout << db.lastError().text().toStdString() << endl;

    list.sort();
    emit appBookReady(list);
}

void dbHandler::Extract(QString start,QString end, QStringList books)
{
    QSqlQuery query(db);

    query.exec(crt_tbl_Production_728);
    //Will be populated with a stored procedure
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);


    setGlobals(start, end, books);
    makeItemAnalysisTable(start, end);

    ////QString string_742_new = QString(query_Hours_Worked_742_base).arg(appSlot).arg(iconCan).arg(iconNS).arg(startDate).arg(endDate).arg(appStart - 1);
    //QString query_Hours_Worked_742 = appendBooksToString(query_Hours_Worked_742_base, m_startDate, m_endDate);

    //cout << query_Hours_Worked_742.toStdString().c_str() << endl;
    //query.exec(query_Hours_Worked_742.toStdString().c_str());
    //cout << db.lastError().text().toStdString() << endl;
    //fflush(stdout);
    //query.next();
    //QString result = query.value(0).toString();
    //cout << result.toStdString() << endl;
    //fflush(stdout);

    //QDateTime time(QDate::currentDate());
    //auto start_time = time.currentMSecsSinceEpoch();

    //cout << getUnbookedRecalls(start, end) << endl;
    //cout << time.currentMSecsSinceEpoch() - start_time << endl;
    //fflush(stdout);

    //start_time = time.currentMSecsSinceEpoch();
    //cout << getLostRecalls(start, end) << endl;
    //cout << time.currentMSecsSinceEpoch() - start_time << endl;
    //fflush(stdout);


    cout << getNonPatientRelatedHours(m_startDate, m_endDate) << endl;
    QDateTime time(QDate::currentDate());
    auto start_time = time.currentMSecsSinceEpoch();
    cout << setprecision(12) << getProduction(m_start_date, m_end_date) << endl;
    cout << time.currentMSecsSinceEpoch() - start_time << endl;
    fflush(stdout);


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
    //    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg("'2020-01-01'").arg("'2020-12-31'");
    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg(start).arg(end);
//    cout << string_726.toStdString().c_str() << endl;

    query.exec(string_726.toStdString().c_str());
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec("SELECT * FROM ITEM_ANALYSIS;");

    //while (query.next())
    //{
    //        cout << query.value(0).toString().toStdString() << "\t";
    //        cout << query.value(1).toString().toStdString() << "\t ";
    //        cout << query.value(2).toString().toStdString() << "\n";
    //        fflush(stdout);
    //}
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);
}

void dbHandler::setGlobals(QString start, QString end, QStringList books)
{
    m_iconCan = 111;
    m_iconNS = 222;
    m_appStart = 22;
    m_appEnd = 33;
    this->m_books = books;

    QSqlQuery query(db);

    m_start_date = start;
    m_end_date = end;

    m_startDate = start.remove("-");
    m_endDate = end.remove("-");

    cout << m_appSlot << endl;

    const char* glb_iconCan = "Select CAST(F5 AS INTEGER)  as CAN from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE' ; ";
    query.exec(glb_iconCan);
    query.next();
    m_iconCan = query.value(0).toInt();
    cout << m_iconCan << endl;

    const char* glb_iconNS = "Select CAST(F6 AS INTEGER)  as NS from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE'; ";
    query.exec(glb_iconNS);
    query.next();
    m_iconNS = query.value(0).toInt();
    cout << m_iconNS << endl;

    const char* glb_appStart = "SELECT CAST(F1 AS INTEGER) as appStart FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    query.exec(glb_appStart);
    query.next();
    m_appStart = query.value(0).toInt();
    cout << m_appStart << endl;

    m_appEnd = apptBookEnd();
    cout << m_appEnd << endl;
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

int dbHandler::getUnbookedRecalls(QString start, QString end)
{
    int result = 0;
    QSqlQuery query(db);
    QString str = QString("Select * from ptpatnts where details like 'Recall%'  and datecreated between date'%1' and date'%2';").arg(start).arg(end);

    query.exec(str.toStdString().c_str());
    while (query.next())
    {
        QString patnumber = query.value(0).toString();
//        cout << patnumber.toStdString() << endl;
        QString datecreated = query.value(4).toString();
//        cout << datecreated.toStdString() << endl;
//        cout << unbkRecall(patnumber, datecreated) << endl;
        result += unbkRecall(patnumber, datecreated);
    }
    return result;
}


int dbHandler::lostRecall(QString PT, QString RD)
{
    QSqlQuery query(db);
    const char* script = "SELECT  count(SKEY)  from paapplns where patnumber = '%1' and entrydate > date'%2' - INTERVAL'1'DAY";
    QString str = QString(script).arg(PT).arg(RD);

    query.exec(str.toStdString().c_str());
    query.next();
//  cout << query.value(0).toString().toStdString() << endl;
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

int dbHandler::getLostRecalls(QString start, QString end)
{
    int result = 0;
    QSqlQuery query(db);
    QString str = QString("Select * from ptpatnts where details like 'Recall%'  and datecreated between date'%1' and date'%2';").arg(start).arg(end);

    query.exec(str.toStdString().c_str());
    while (query.next())
    {
        QString patnumber = query.value(0).toString();
        //        cout << patnumber.toStdString() << endl;
        QString datecreated = query.value(4).toString();
        //        cout << datecreated.toStdString() << endl;
        //        cout << unbkRecall(patnumber, datecreated) << endl;
        result += lostRecall(patnumber, datecreated);
    }
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


int dbHandler::getNonPatientRelatedHours(QString start, QString end)
{
//    Select sum(apptUsed(SKEY, timeused * 5, 21)) / 60 as nonptHr from paapplns where  SKEY BETWEEN '20200101%' AND '20201231%' and (patnumber = '000000' or patnumber = '') and (substring(skey from 13 for 4) = '0001' OR substring(skey from 13 for 4) = '0002' OR substring(skey from 13 for 4) = '0005') AND CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER) > 5;
//    const char* base = "Select sum(apptUsed(SKEY, timeused * 5, 21)) / 60 as nonptHr from paapplns where  SKEY BETWEEN '%1%' AND '%2%' and (patnumber = '000000' or patnumber = '') AND CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER) > 5 AND ";
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

    cout << str.toStdString() << endl;

    QSqlQuery query(db);
    int result = 0;

    query.exec(str.toStdString().c_str());
    while (query.next())
    {
        QString SKEY = query.value(0).toString();
        int timeused = query.value(17).toInt();

        result += apptUsed(SKEY, timeused * m_appSlot, m_appEnd);// "21" is hardcoded instead of value of m_appEnd
    }
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

