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
}

void dbHandler::doQueries()
{

    const char* myQuery = "SELECT * FROM pbpatmas;";

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

    while (query.next())
    {
    //    QString smthng = query.value(3).toString();
    //    //         cout << "result:\n";
        //cout << query.value(2).toString().toStdString() << " " <<
        //    query.value(3).toString().toStdString() << endl;
        //fflush(stdout);
    }
    cout << db.lastError().text().toStdString() << endl;

	//std::cout << "test\n";
 //   fflush(stdout);
	//Sleep(3000);
	emit allCompleted();
}

