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

}


void dbHandler::loadBooksAndFunctions()
{
    QSqlQuery query(db);

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
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

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


////    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg("'2020-01-01'").arg("'2020-12-31'");
//    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg(start).arg(end);
//    cout << string_726.toStdString().c_str() << endl;
//
//    query.exec(string_726.toStdString().c_str());
//    cout << db.lastError().text().toStdString() << endl;
//    fflush(stdout);
//
//    query.exec("SELECT * FROM ITEM_ANALYSIS;");
//
//    while (query.next())
//    {
//            cout << query.value(0).toString().toStdString() << "\t";
//            cout << query.value(1).toString().toStdString() << "\t ";
//            cout << query.value(2).toString().toStdString() << "\n";
//            fflush(stdout);
//    }
//    cout << db.lastError().text().toStdString() << endl;
//    fflush(stdout);

    QString appSlot = "$appSlot";
    QString iconCan = "$iconCan";
    QString iconNS = "$iconNS";
    QString appStart = "$appStart";
    QString appEnd = "$appEnd";

    const char* glb_appSlot = "SELECT CAST(F2 AS INTEGER) + 1 AS appbooklength FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    query.exec(glb_appSlot);
    query.next();
    QString appSlot_tmp = query.value(0).toString();
    bool ok;
    int tmp =  60/appSlot_tmp.toInt(&ok);
//    cout << tmp << endl;
    appSlot = QString::number(tmp);
    cout << appSlot.toStdString().c_str() << endl;


    const char* glb_iconCan = "Select CAST(F5 AS INTEGER)  as CAN from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE' ; ";
    query.exec(glb_iconCan);
    query.next();
    iconCan = query.value(0).toString();
    cout << iconCan.toStdString().c_str() << endl;

    const char* glb_iconNS = "Select CAST(F6 AS INTEGER)  as NS from sytblent where substring (skey from 1 for 9 ) = 'APPSIXRFE'; ";
    query.exec(glb_iconNS);
    query.next();
    iconNS = query.value(0).toString();
    cout << iconNS.toStdString().c_str() << endl;

    const char* glb_appStart = "SELECT CAST(F1 AS INTEGER) as appStart FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    query.exec(glb_appStart);
    query.next();
    appStart = query.value(0).toString();
    cout << appStart.toStdString().c_str() << endl;

    const char* glb_appEnd = " Select apptbookend() FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';";
    query.exec(glb_appEnd);
    query.next();
    appEnd = query.value(0).toString();
    cout << appEnd.toStdString().c_str() << endl;


    QString startDate = "20200701";
    QString endDate = "20200731";

    QString string_742 = QString(query_Hours_Worked_742).arg(appSlot).arg(iconCan).arg(iconNS).arg(startDate).arg(endDate)
                                .arg(books.at(0)).arg(books.at(1)).arg(books.at(2)).arg(appStart.toInt(&ok)-1);

    cout << string_742.toStdString().c_str() << endl;
    query.exec(string_742.toStdString().c_str());
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);
    query.next();
    QString result = query.value(0).toString();
//    cout << query.value(0).toString().toStdString().c_str() << endl;
    cout << query.value(0).toString().toStdString().c_str() << endl;
//    cout << query.value(2).toString().toStdString().c_str() << endl;
    fflush(stdout);
    emit extractionCompleted();
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

