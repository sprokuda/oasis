#include "dbHandler.h"
#include <iomanip>
using namespace std;

extern const char* query_Hours_Worked_742_base;
extern const char* query_Hours_Cancelled_743_base;
extern const char* query_Number_Of_Appointments_748_base;
extern const char* query_All_Patients_749;
extern const char* query_Active_Patients_7410;

extern const char* query_New_Patients_7411_base;
extern const char* query_Churned_Patients_7412_base;
extern const char* query_Unique_Patients_7413_base;

extern const char* query_Lapsed_Patients_7414;
extern const char* query_Total_Recalls_7418_base;
extern const char* query_Total_Incomplete_Treatment_Value_7421;
extern const char* query_Treatment_Plans_Created_7422_base;
extern const char* query_Treatment_Plans_Not_Accepted_7423_base;

extern const char* query_Debtors_7432;
extern const char* query_Top_10_Items_By_Value_7433;
extern const char* query_Top_10_Items_by_Count_7434;

double dbHandler::Production(QString start, QString end)
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

	log_query_result("Production for interval: " + start + "/" + end, db.lastError().text());

	writeoff = query.value(0).toString().toDouble();

	return invoice + adjust - discount - writeoff;;
}

QString dbHandler::daysInMonth(const int& month)
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
}

int dbHandler::daysInFebuary(const int& year)//todo - implement
{
	int days = 28;

	if (year % 4 == 0) 
	{
		if (year % 100 == 0) 
		{
			if (year % 400 == 0) days = 29;//cout << year << " is a leap year.";
			else days = 28;// cout << year << " is not a leap year.";
		}
		else days = 29;//cout << year << " is a leap year.";
	}
	else days = 28;//cout << year << " is not a leap year.";

	return days;//28
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
//	cout << "number of monthes = " << n_monthes << endl;

	auto lastDayOfMonth=[=](int month, int year) 
	{  
		int result = 0;
		switch (month)
		{
		case 1: result = 31; break;
		case 2: result = daysInFebuary(year); break;//todo leap years
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

	auto nameOfMonth = [=](int month)
	{
		QString result = 0;
		switch (month)
		{
		case 1: result = "Jan"; break;
		case 2: result = "Feb"; break;//todo leap years
		case 3: result = "Mar"; break;
		case 4: result = "Apr"; break;
		case 5: result = "May"; break;
		case 6: result = "Jun"; break;
		case 7: result = "Jul"; break;
		case 8: result = "Aug"; break;
		case 9: result = "Sep"; break;
		case 10: result = "Oct"; break;
		case 11: result = "Nov"; break;
		case 12: result = "Dec"; break;
		default: result = "null";
		}
		return result;
	};

	int month = first_month;
	int year = first_year;
//	cout << endl;
	m_dates.clear();
	m_months.clear();
	m_header_months.clear();

	for (int i = 0; i < n_monthes; i++)
	{
		auto str_month = QString::number(month);
		if (str_month.size() == 1) str_month = "0" + str_month;

		auto local_date_start = QString::number(year) + "-" + str_month + "-" + QString("01");
		auto local_date_end = QString::number(year) + "-" + str_month + "-" + lastDayOfMonth(month,year);
//		cout << local_date_start.toStdString() << "\t" << local_date_end.toStdString() << endl;

		m_dates.push_back(make_pair(local_date_start, local_date_end)); 
		m_months.push_back(QString::number(year) + "-" + str_month);
		m_header_months.push_back(nameOfMonth(month) + "-" + QString::number(year).right(2));
		if (month < 12) month++;
		else if (month == 12)
		{
			month = 1;
			year++;
		}
	}
	writer->writeHeader(m_header_months);
}

void dbHandler::getHoursWorked()
{
	QSqlQuery query(db);
	m_HoursWorked.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
	QString query_Hours_Worked_742 = appendBooksToString(query_Hours_Worked_742_base, 
		QString(it->first).remove("-"), QString(it->second).remove("-")); //QString(it->second).remove("-")

	//cout << query_Hours_Worked_742.toStdString().c_str() << endl;
	query.exec(query_Hours_Worked_742.toStdString().c_str());
	query.next();
	auto result = query.value(0).toString().toInt();
	log_query_result("Hours Worked for for interval: " + it->first + "/" + it->second, db.lastError().text());
	m_HoursWorked.push_back(result);
	}
	writer->writeArray("Hours Worked", m_HoursWorked);
}

void dbHandler::getHoursCancelled()
{
	QSqlQuery query(db);
	m_HoursCancelled.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_Hours_Cancelled_743 = appendBooksToString(query_Hours_Cancelled_743_base, 
			QString(it->first).remove("-"), QString(it->second).remove("-"));
		if (m_iconCan == 0 && m_iconNS == 0)
		{
			m_HoursCancelled.push_back(0);
		}
		else
		{
			query.exec(query_Hours_Cancelled_743.toStdString().c_str());
			query.next();
			auto result = query.value(0).toString().toInt();
			log_query_result("Hours Cancelled for interval: " + it->first + "/" + it->second, db.lastError().text());
			m_HoursCancelled.push_back(result);
		}
	}
	writer->writeArray("Hours Cancelled", m_HoursCancelled);
}


void dbHandler::getNonPatientRelatedHours()
{
	m_NonPatientRelatedHours.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		m_NonPatientRelatedHours.push_back(NonPatientRelatedHours(QString(it->first).remove("-"), QString(it->second).remove("-")));
	}
	writer->writeArray("Non-Patient Related Hours", m_NonPatientRelatedHours);
}

void dbHandler::getOtherHours()
{
	m_CalendarHours.clear();
	m_AvailableHours.clear();

	auto numberOfMonth = [](const QString& start, const QString& end)
	{
		auto start_year = start.split("-").at(0).toInt();
		auto start_month = start.split("-").at(1).toInt();

		auto end_year = end.split("-").at(0).toInt();
		auto end_month = end.split("-").at(1).toInt();

		if (end_year == start_year)
			return end_month - start_month + 1;
		//else if (end_year == start_year + 1)
		//	return (12 - start_month) + end_month + 1;
		else
			return (end_year - start_year - 1)*12 + (12 - start_month) + end_month + 1;
	};

	auto it1 = m_dates.begin();
	auto it2 = m_NonPatientRelatedHours.begin();
	for (; it1 != m_dates.end() || it2 != m_NonPatientRelatedHours.end(); it1++, it2++)
	{
		auto calendar_hours = numberOfMonth(it1->first,it1->second) * 30 * m_bookLength * m_prodCol;
		m_CalendarHours.push_back(calendar_hours);
		m_AvailableHours.push_back(calendar_hours - *it2);
	}
	writer->writeArray("Calendar Hours", m_CalendarHours);
	writer->writeArray("Available Hours", m_AvailableHours);
}

void dbHandler::getUtilisation()
{
	m_Utilisation.clear();

	auto it1 = m_HoursWorked.begin();
	auto it2 = m_AvailableHours.begin();
	for (; it1 != m_HoursWorked.end() && it2 != m_AvailableHours.end(); ++it1 , ++it2)
	{
		if(*it2 != 0)
			m_Utilisation.push_back((100*(*it1) / (*it2)));
		else
			m_Utilisation.push_back(0);

	}
	writer->writeArray("Utilisation", m_Utilisation,"","%");

}

void dbHandler::getNumberOfAppointments()
{
	QSqlQuery query(db);
	m_NumberOfAppointments.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_Number_Of_Appointments_748 = appendBooksToStringNoAppSlot(query_Number_Of_Appointments_748_base, 
			QString(it->first).remove("-"), QString(it->second).remove("-"));

		query.exec(query_Number_Of_Appointments_748.toStdString().c_str());
		query.next();
		auto result = (int)query.value(0).toString().toDouble();
		log_query_result("Number Of Appointments for interval: " + it->first + "/" + it->second, db.lastError().text());

		m_NumberOfAppointments.push_back(result);
	}
	writer->writeArray("Number of Appointments", m_NumberOfAppointments);
}


void dbHandler::getAllAndActivePatients()
{
	QSqlQuery query(db);

	query.exec(query_All_Patients_749);
	query.next();
	auto all = query.value(0).toString().toInt();
	log_query_result("All Patients", db.lastError().text());

	writer->writeSnapshot("All Patients", all);

	query.exec(query_Active_Patients_7410);
	query.next();
	auto active = query.value(0).toString().toInt();
	log_query_result("Active Patients", db.lastError().text());

	writer->writeSnapshot("Active Patients", active);

	writer->writeSnapshot("Inactive Patients", all - active);
}


void dbHandler::getNewPatients()
{
	QSqlQuery query(db);
	m_NewPatients.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_New_Patients_7411 = QString(query_New_Patients_7411_base).arg(it->first).arg(it->second);

		query.exec(query_New_Patients_7411.toStdString().c_str());
		query.next();
		auto result = query.value(0).toString().toInt();
		log_query_result("New Patients for interval: " + it->first + "/" + it->second, db.lastError().text());

		m_NewPatients.push_back(result);
	}
	writer->writeArray("New Patients", m_NewPatients);
}


void dbHandler::getChurnedPatients()
{
	QSqlQuery query(db);
	m_ChurnedPatients.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_Churned_Patients_7412 = QString(query_Churned_Patients_7412_base).arg(it->first).arg(it->second);//m_startDate, m_endDate;

		query.exec(query_Churned_Patients_7412.toStdString().c_str());
		query.next();
		auto result = query.value(0).toString().toInt();
		log_query_result("Churned Patients for interval: " + it->first + "/" + it->second, db.lastError().text());

		m_ChurnedPatients.push_back(result);
	}
	writer->writeArray("Churned Patients", m_ChurnedPatients);
}

void dbHandler::getUniquePatients()
{
	QSqlQuery query(db);
	m_UniquePatients.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_Unique_Patients_7413 = QString(query_Unique_Patients_7413_base).arg(it->first).arg(it->second);//m_startDate, m_endDate;

		query.exec(query_Unique_Patients_7413.toStdString().c_str());
		query.next();
		auto result = query.value(0).toString().toInt();
		log_query_result("Unique Patients for interval: " + it->first + "/" + it->second, db.lastError().text());

		m_UniquePatients.push_back(result);
	}
	writer->writeArray("Unique Patients", m_UniquePatients);
}

void dbHandler::getLapsedPatients()
{
	QSqlQuery query(db);

	query.exec(query_Lapsed_Patients_7414);
	query.next();
	auto result = query.value(0).toString().toInt();
	log_query_result("Lapsed Patients", db.lastError().text());

	writer->writeSnapshot("Lapsed Patients", result);
}

void dbHandler::getNewPatientPercent()
{
	m_NewPatientPercent.clear();

	auto it1 = m_NewPatients.begin();
	auto it2 = m_UniquePatients.begin();
	for (; it1 != m_NewPatients.end() && it2 != m_UniquePatients.end(); ++it1, ++it2)
	{
		if (*it2 != 0)
			m_NewPatientPercent.push_back((100 * (*it1) / (*it2)));
		else
			m_NewPatientPercent.push_back(0);

	}
	writer->writeArray("New Patient %", m_NewPatientPercent, "", "%");

}

void dbHandler::getNetPatientGain()
{
	m_NetPatientGain.clear();

	auto it1 = m_NewPatients.begin();
	auto it2 = m_ChurnedPatients.begin();
	for (; it1 != m_NewPatients.end() && it2 != m_ChurnedPatients.end(); ++it1, ++it2)
	{
			m_NetPatientGain.push_back(*it1 - *it2);
	}
	writer->writeArray("Net Patient Gain", m_NetPatientGain, "", "");
}


void dbHandler::getUnbookedRecalls()
{
	m_UnbookedRecalls.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		m_UnbookedRecalls.push_back(UnbookedRecalls(QString(it->first), QString(it->second)));
	}
	writer->writeArray("Unbooked Recalls", m_UnbookedRecalls);
}


void dbHandler::getTotalRecalls()
{
	QSqlQuery query(db);
	m_TotalRecalls.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_Total_Recalls_7418 = QString(query_Total_Recalls_7418_base).arg(it->first).arg(it->second);//m_startDate, m_endDate;

		query.exec(query_Total_Recalls_7418.toStdString().c_str());
		query.next();
		auto result = query.value(0).toString().toInt();
		log_query_result("Total Recalls for interval:" + it->first + "/" + it->second, db.lastError().text());

		m_TotalRecalls.push_back(result);
	}
	writer->writeArray("Total Recalls", m_TotalRecalls);
}


void dbHandler::getRecallEffectiveness()
{
	m_RecallEffectiveness.clear();

	auto it1 = m_TotalRecalls.begin();
	auto it2 = m_UnbookedRecalls.begin();
	for (; it1 != m_TotalRecalls.end() && it2 != m_UnbookedRecalls.end(); ++it1, ++it2)
	{
		if (*it1 != 0)
			m_RecallEffectiveness.push_back((100 * ((*it1) - (*it2))/ (*it1)));
		else
			m_RecallEffectiveness.push_back(0);

	}
	writer->writeArray("Recall Effectiveness %", m_RecallEffectiveness, "", "%");

}


void dbHandler::getLostRecalls()
{
	m_LostRecalls.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		m_LostRecalls.push_back(LostRecalls(QString(it->first), QString(it->second)));
	}
	writer->writeArray("Lost Recalls", m_LostRecalls);
}



void dbHandler::getTotalIncompleteTreatmentValue()
{
	QSqlQuery query(db);

	query.exec(query_Total_Incomplete_Treatment_Value_7421);
	query.next();
	auto result = (int)query.value(0).toString().toDouble();
	log_query_result("Total Incomplete Treatment Value", db.lastError().text());
	writer->writeSnapshot("Total Incomplete Treatment Value", result,"\"$","\"");
}

void dbHandler::getTreatmentPlansCreated()
{
	QSqlQuery query(db);
	m_TreatmentPlansCreated.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_Treatment_Plans_Created_7422 = QString(query_Treatment_Plans_Created_7422_base).arg(it->first).arg(it->second);//m_startDate, m_endDate;

		query.exec(query_Treatment_Plans_Created_7422.toStdString().c_str());
		query.next();
		auto result = (int)query.value(0).toString().toDouble();
		log_query_result("Treatment Plans Created for interval: " + it->first + "/" + it->second, db.lastError().text());

		m_TreatmentPlansCreated.push_back(result);
	}
	writer->writeArray("Treatment Plans Created", m_TreatmentPlansCreated, "\"$", "\"");
}


void dbHandler::getTreatmentPlansNotAccepted()
{
	QSqlQuery query(db);
	m_TreatmentPlansNotAccepted.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		QString query_Treatment_Plans_Not_Accepted_7423 = QString(query_Treatment_Plans_Not_Accepted_7423_base).arg(it->first).arg(it->second);//m_startDate, m_endDate;

		query.exec(query_Treatment_Plans_Not_Accepted_7423.toStdString().c_str());
		query.next();
		auto result = (int)query.value(0).toString().toDouble();
		log_query_result("Treatment Plans Not Accepted for interval: " + it->first + "/" + it->second, db.lastError().text());

		m_TreatmentPlansNotAccepted.push_back(result);
	}
	writer->writeArray("Treatment Plans Not Accepted", m_TreatmentPlansNotAccepted, "\"$", "\"");
}

void dbHandler::getTreatmentPlanConversionRate()
{
	m_TreatmentPlanConversionRate.clear();

	auto it1 = m_TreatmentPlansCreated.begin();
	auto it2 = m_TreatmentPlansNotAccepted.begin();
	for (; it1 != m_TreatmentPlansCreated.end() && it2 != m_TreatmentPlansNotAccepted.end(); ++it1, ++it2)
	{
		if (*it1 != 0)
			m_TreatmentPlanConversionRate.push_back((100 * ((*it1) - (*it2)) / (*it1)));
		else
			m_TreatmentPlanConversionRate.push_back(0);

	}
	writer->writeArray("Treatment Plan Conversion Rate %", m_TreatmentPlanConversionRate, "", "%");

}

void dbHandler::getProduction()
{
	QSqlQuery query(db);
	m_Production.clear();
	for (auto it = m_dates.begin(); it != m_dates.end(); it++)
	{
		m_Production.push_back((int)Production(it->first,it->second));
	}
	writer->writeArray("Total Production", m_Production, "\"$", "\"");
}

void dbHandler::getProductionPerValue(const QString& header, const vector<int>& hours)
{
	vector<int> prd_per_hour;

	auto it1 = m_Production.begin();
	auto it2 = hours.begin();
	for (; it1 != m_Production.end() && it2 != hours.end(); ++it1, ++it2)
	{
		if (*it2 != 0)
			prd_per_hour.push_back(((*it1)  / (*it2)));
		else
			prd_per_hour.push_back(0);

	}
	writer->writeArray(header, prd_per_hour, "\"$", "\"");

}

void dbHandler::getProductionThroughLost(const QString& header, const vector<int>& hours, const vector<int>& lost)
{
	double prd_per_hour = 0;
	vector<int> lrtc;

	auto it1 = m_Production.begin();
	auto it2 = hours.begin();
	auto it3 = lost.begin();
	for (; it1 != m_Production.end() && it2 != hours.end() && it3 != lost.end(); ++it1, ++it2, ++it3)
	{
		if (*it2 != 0)
			prd_per_hour=(double)(*it1) / (double)(*it2);
		else
			prd_per_hour=0;
		lrtc.push_back((int)(prd_per_hour * (double)*it3));
	}
	writer->writeArray(header, lrtc, "\"$", "\"");

}

void dbHandler::getDebtors()
{
	QSqlQuery query(db);

	query.exec(query_Debtors_7432);
	//cout << db.lastError().text().toStdString() << endl;
	//fflush(stdout);
	query.next();
	auto result = (int)query.value(0).toString().toDouble();
	log_query_result("Debtors", db.lastError().text());

	writer->writeSnapshot("Debtors", result, "\"$", "\"");
}


void dbHandler::getTop10Items(const QString& header, const QString& str, const QString prefix)
{
	vector<pair<QString, int>> vec;

	QSqlQuery query(db);
	query.exec(str.toStdString().c_str());
	while (query.next())
	{
		auto first = query.value(0).toString();
		auto second = (int)query.value(1).toString().toDouble();
		vec.push_back(make_pair(first, second));
	}

	sort(vec.begin(), vec.end(), [](auto a, auto b) {return a.second > b.second; });

	writer->writeTop10(header, vec, prefix);
}

void dbHandler::writeGlobals(const QDate& current_date, const QTime& current_time)
{
	auto out = QTextStream(writer->getFilePtr());
	out << "Practice Name" << ","<< m_practice << "\n";
	auto date = m_start_date.split("-");
	out << "Start Date" << "," << date.at(2)<< "/" << date.at(1) << "/" << date.at(0) << "\n";
	date = m_end_date.split("-");
	out << "End Date" << "," << date.at(2) << "/" << date.at(1) << "/" << date.at(0) << "\n";
	out << "Production Columns" << "," << m_prodCol << "\n";

	auto books_names = [=]()
	{
		QStringList result;
		m_books.sort();
		auto it1 = m_books.begin();
		while (it1 != m_books.end())
		{
			for (auto it = m_books_map.begin(); it != m_books_map.end() && it1 != m_books.end(); it++)
			{
				if (it->second == it1->toStdString())
				{
					result.push_back(it->first.c_str());
					it1++;
				}
			}
		}
		result.sort();
		return result;// result.join(",");
	};

	auto books_names_simplified = [=]()
	{

		map <string, string> book_numbers;
		for (auto it = m_books_map.begin(); it != m_books_map.end(); it++)
		{
			book_numbers.emplace(it->second, it->first);
		}

		QStringList result;
		m_books.sort();

		auto it1 = m_books.begin();
		for (auto it = book_numbers.begin(); it != book_numbers.end() && it1 != m_books.end(); it++)
		{
			if (it->first == it1->toStdString())
			{
				result.push_back(it->second.c_str());
				it1++;
			}
		}

		result.sort();
		return result;// result.join(",");

	};




	out << "Appointment Books" << "," << "\"" << books_names_simplified().join(",") << "\"" << "\n";
	out << "Date of Extraction" << "," << current_date.toString("dd/MM/yyyy") << "\n";
	out << "Time of Extraction" << "," << current_time.toString("hh:mm:ss");
}