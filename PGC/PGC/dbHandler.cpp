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


//    Sleep(3000);
    queryAppBook();
    //emit allCompleted();
}

void dbHandler::queryAppBook()
{
    const char* script = "SELECT * FROM APP_BOOK;";
    QStringList list;// = { "0022","0021","0023" };

    QSqlQuery query(db);

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

void dbHandler::Extract(QString start,QString end)
{
    QSqlQuery query(db);
    query.exec(crt_tbl_Production_728);
    //Will be populated with a stored procedure
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);



//    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg("'2020-01-01'").arg("'2020-12-31'");
    QString string_726 = QString(ppl_tbl_ITEM_ANALYSIS_726).arg(start).arg(end);
    cout << string_726.toStdString().c_str() << endl;

    query.exec(string_726.toStdString().c_str());
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    query.exec("SELECT * FROM ITEM_ANALYSIS;");

    while (query.next())
    {
            cout << query.value(0).toString().toStdString() << "\t";
            cout << query.value(1).toString().toStdString() << "\t ";
            cout << query.value(2).toString().toStdString() << "\n";
            fflush(stdout);
    }
    cout << db.lastError().text().toStdString() << endl;
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

