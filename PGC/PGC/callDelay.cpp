#include<windows.h>

#include "callDelay.h"
//#include "dbScripts.h"

using namespace std;

//extern const char* crt_tbl_FIRST_INV_721;

callDelay::callDelay(QObject* parent) : QObject(parent)
{

}

callDelay::~callDelay()
{

}

void callDelay::doDelay()
{
    Sleep(250);
	emit delayFinished();
}

