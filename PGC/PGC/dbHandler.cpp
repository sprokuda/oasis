#include<windows.h>

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


    setGlobals(start, end);
    makeItemAnalysisTable(start, end);




//    QString string_742 = QString(query_Hours_Worked_742).arg(appSlot).arg(iconCan).arg(iconNS).arg(startDate).arg(endDate)
//                                .arg(books.at(0)).arg(books.at(1)).arg(books.at(2)).arg(appStart-1);

    //QString string_742_new = QString(query_Hours_Worked_742_base).arg(appSlot).arg(iconCan).arg(iconNS).arg(startDate).arg(endDate).arg(appStart - 1);
    //for (int i = 0; i < books.size(); i++)
    //{
    //    if(i == 0) string_742_new.append("(");

    //    if (i < books.size() - 1)
    //        string_742_new.append(QString(query_Hours_Worked_742_book).arg(books.at(i)));
    //    else
    //    {
    //        string_742_new.append(QString(query_Hours_Worked_742_book).arg(books.at(i)).remove(QString("OR")));
    //        string_742_new.append(");");
    //    }
    //}

    //cout << string_742_new.toStdString().c_str() << endl;
    //query.exec(string_742_new.toStdString().c_str());
    //cout << db.lastError().text().toStdString() << endl;
    //fflush(stdout);
    //query.next();
    //QString result = query.value(0).toString();
    //cout << result.toStdString() << endl;
    //fflush(stdout);

    QDateTime time(QDate::currentDate());
    auto start_time = time.currentMSecsSinceEpoch();

    //cout << getUnbookedRecalls("2021-07-01", "2021-07-31") << endl;
    //cout << time.currentMSecsSinceEpoch() - start_time << endl;
    //fflush(stdout);

    start_time = time.currentMSecsSinceEpoch();
    cout << getLostRecalls("2021-07-01", "2021-07-31") << endl;
    cout << time.currentMSecsSinceEpoch() - start_time << endl;
    fflush(stdout);

    emit extractionCompleted();
}


int dbHandler::apptBookEnd()
{
    const char* crt_st = "SELECT CAST(F1 AS INTEGER) FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    const char* crt_hrs = "SELECT CAST(F2 AS INTEGER) INTO  FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000'";

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
    cout << string_726.toStdString().c_str() << endl;

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

void dbHandler::setGlobals(QString start, QString end)
{
    iconCan = 111;
    iconNS = 222;
    appStart = 22;
    appEnd = 33;

    QSqlQuery query(db);

    start_date = start;
    end_date = end;

    startDate = start.remove("-");
    endDate = end.remove("-");

    cout << appSlot << endl;

    const char* glb_iconCan = "Select CAST(F5 AS INTEGER)  as CAN from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE' ; ";
    query.exec(glb_iconCan);
    query.next();
    iconCan = query.value(0).toInt();
    cout << iconCan << endl;

    const char* glb_iconNS = "Select CAST(F6 AS INTEGER)  as NS from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE'; ";
    query.exec(glb_iconNS);
    query.next();
    iconNS = query.value(0).toInt();
    cout << iconNS << endl;

    const char* glb_appStart = "SELECT CAST(F1 AS INTEGER) as appStart FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    query.exec(glb_appStart);
    query.next();
    appStart = query.value(0).toInt();
    cout << appStart << endl;

    appEnd = apptBookEnd();
    cout << appEnd << endl;
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
//    const char* script = "SELECT  count(SKEY)  from paapplns where patnumber = '%1' and entrydate between date'%2' and date'%3' + INTERVAL'30'DAY;";
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

