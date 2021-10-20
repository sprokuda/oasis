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

void dbHandler::generateDates()
{
	auto first_month = m_start_date.split("-").at(1).toInt();
	auto first_year = m_start_date.split("-").at(0).toInt();

	auto last_month = m_end_date.split("-").at(1).toInt();
	auto last_year = m_end_date.split("-").at(0).toInt();

	int n_monthes = 0;
	if(first_year == last_year)
	n_monthes = last_month - first_month + 1;
	else if (first_year == last_year - 1)
	n_monthes = (12 - first_month) + last_month + 1;
	else 
	n_monthes = (last_year - first_year - 1) * 12 + (12 - first_month) + last_month + 1;
	cout << "number of monthes = " << n_monthes << endl;

	auto lastDayOfMonth=[](int month) 
	{  
		int result = 0;
		switch (month)
		{
		case 1: result = 31; break;
		case 2: result = 28; break;//todo leap years
		case 3: result = 31; break;
		case 4: result = 30; break;
		case 5: result = 31; break;
		case 6: result = 30; break;
		case 7: result = 31; break;
		case 8: result = 31; break;
		case 9: result = 30; break;
		case 10: result = 31; break;
		case 11: result = 30; break;
		case 12: result = 31; break;
		default: result = 33;
		}
		return QString::number(result);
	};

	int month = first_month;
	int year = first_year;
	cout << endl;
	for (int i = 0; i < n_monthes; i++)
	{
		auto str_month = QString::number(month);
		if (str_month.size() == 1) str_month = "0" + str_month;

		auto local_date_start = QString::number(year) + "-" + str_month + "-" + QString("01");
		auto local_date_end = QString::number(year) + "-" + str_month + "-" + lastDayOfMonth(month);
		cout << local_date_start.toStdString() << "\t" << local_date_end.toStdString() << endl;

		if (month < 12) month++;
		else if (month == 12)
		{
			month = 1;
			year++;
		}
	}
}

