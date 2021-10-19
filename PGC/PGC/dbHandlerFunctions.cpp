#include "dbHandler.h"
#include <iomanip>
using namespace std;


#include <sstream>
#include <string>
template<typename T>
T StringToNumber(const std::string& numberAsString)
{
	T valor;

	std::stringstream stream(numberAsString);
	stream >> valor;
	if (stream.fail()) {
		std::runtime_error e(numberAsString);
		throw e;
	}
	return valor;
}

double dbHandler::getProduction(QString start, QString end)
{
//DECLARE invoice DECIMAL(15, 2);
//DECLARE Adjust DECIMAL(15, 2);
//DECLARE discount DECIMAL(15, 2);
//DECLARE Writeoff DECIMAL(15, 2);
//DECLARE Prod DECIMAL(15, 2);
	QSqlQuery query(db);

	double invoice;
	double adjust;
	double discount;
	double writeoff;

	QString str = QString("SELECT Sum(Amount) from pbarcmas  where transtype = 1 and deleted <> -1 and entrydate  between date'%1' and date'%2';").arg(start).arg(end);
	query.exec(str.toStdString().c_str());
	query.next();
	invoice = query.value(0).toString().toDouble();
//	cout << setprecision(12) << invoice << endl;

	str = QString("SELECT Sum(Amount) from pbarcmas  where transtype = 2 and deleted <> -1 and entrydate  between date'%1' and date'%2';").arg(start).arg(end);
	query.exec(str.toStdString().c_str());
	query.next();
//	auto tmp = query.value(0).toString();
	adjust = query.value(0).toString().toDouble();

	str = QString("SELECT Sum(Amount) from pbarcmas  where transtype = 4 and deleted <> -1 and entrydate  between date'%1' and date'%2';").arg(start).arg(end);
	query.exec(str.toStdString().c_str());
	query.next();
	discount = query.value(0).toString().toDouble();

	str = QString("SELECT Sum(Amount) from pbarcmas  where transtype = 5 and deleted <> -1 and entrydate  between date'%1' and date'%2';").arg(start).arg(end);
	query.exec(str.toStdString().c_str());
	query.next();
	writeoff = query.value(0).toString().toDouble();

	return invoice + adjust - discount - writeoff;;
}



//@
//CREATE PROCEDURE  Production(IN A DATE, IN  B DATE)
//MODIFIES SQL DATA
//BEGIN
//DECLARE invoice DECIMAL(15, 2);
//DECLARE Adjust DECIMAL(15, 2);
//DECLARE discount DECIMAL(15, 2);
//DECLARE Writeoff DECIMAL(15, 2);
//DECLARE Prod DECIMAL(15, 2);
//DELETE FROM PRODUCTION;
//SELECT   Sum(Amount) INTO invoice  from pbarcmas  where transtype = 1 and deleted <> -1 and entrydate  between A and B;
//SELECT  Sum(Amount) INTO Adjust  from pbarcmas  where transtype = 2 and deleted <> -1 and entrydate  between A and B;
//SELECT   Sum(Amount) INTO discount  from pbarcmas  where transtype = 4 and deleted <> -1 and entrydate  between A and B;
//SELECT   Sum(Amount) INTO Writeoff from pbarcmas  where transtype = 5 and deleted <> -1 and entrydate  between A and B;
//IF invoice is null then
//set invoice = 0;
//END IF;
//IF Adjust is null then
//set Adjust = 0;
//END IF;
//IF discount is null then
//set discount = 0;
//END IF;
//IF Writeoff is null then
//set Writeoff = 0;
//END IF;
//SET Prod = invoice + Adjust - discount - Writeoff;
//INSERT INTO PRODUCTION(Prd) VALUES(Prod);
//END
//@

