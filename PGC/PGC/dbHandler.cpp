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
}

void dbHandler::queryAppBook()
{
    const char* script = "SELECT * FROM APP_BOOK;";
    QStringList list = { "0022","0021","0023" };

    QSqlQuery query(db);

    //query.exec(script);
    //cout << db.lastError().text().toStdString() << endl;
    //fflush(stdout);

    //while (query.next())
    //{
    //    list << query.value(1).toString();
    //}
    //cout << db.lastError().text().toStdString() << endl;

    list.sort();
    emit appBookReady(list);
}
void dbHandler::doQueries()
{
    const char* script = "SELECT * FROM pbpatmas;";
    QStringList list;
    QSqlQuery query(db);

    query.exec(script);
    cout << db.lastError().text().toStdString() << endl;
    fflush(stdout);

    while (query.next())
    {
    }
    cout << db.lastError().text().toStdString() << endl;

	//std::cout << "test\n";
 //   fflush(stdout);
	//Sleep(3000);
	emit allCompleted();
}

