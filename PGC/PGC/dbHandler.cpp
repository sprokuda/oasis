#include "dbHandler.h"
#include<windows.h>

dbHandler::dbHandler(QObject* parent) : QObject(parent)
{

}

void dbHandler::doQueries()
{
//	QTest::qSleep(3000);

//	Sleep(30);
	emit allCompleted();
}

