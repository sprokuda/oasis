#include "logOfPGC.h"


void logOfPGC::appendString(QString str)
{ 
	if(str != QString("\n")) 	log << str.toStdString(); 
}