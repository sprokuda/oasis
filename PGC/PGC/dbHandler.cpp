#include "dbHandler.h"
#include<windows.h>

using namespace std;

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
    }
}

void dbHandler::doQueries()
{

    const char* myQuery = "SELECT * FROM pbpatmas;";

    QSqlQuery query(db);
    query.exec(myQuery);

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
	//Sleep(3000);
	emit allCompleted();
}

