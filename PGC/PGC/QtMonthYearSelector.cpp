#include "QtMonthYearSelector.h"




QtMonthYearSelector::QtMonthYearSelector(QWidget* parent)
    : QWidget(parent)
{
    QDate curr_date = QDate::currentDate();
    edit = new QLineEdit(QString::number(QDate::currentDate().month()) + "/" + QString::number(QDate::currentDate().year()));
    edit->setEnabled(false);
    month = new QComboBox(this);
    month->addItems(months);
    month->setCurrentIndex(QDate::currentDate().month()-1);
/*
    January – 31 days
        February – 28 days in a common year and 29 days in leap years
        March – 31 days
        April – 30 days
        May – 31 days
        June – 30 days
        July – 31 days
        August – 31 days
        September – 30 days
        October – 31 days
        November – 30 days
        December – 31 days
*/
    year = new QSpinBox(this);
    year->setRange(2001, QDate::currentDate().year());
    year->setValue(QDate::currentDate().year());

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(edit);
    mainLayout->addWidget(month);
    mainLayout->addWidget(year);
    setLayout(mainLayout);

    connect(month, SIGNAL(currentTextChanged(QString)), SLOT(onMonthChange(QString)));
    connect(year, SIGNAL(valueChanged(int)), SLOT(onYearChange(int)));
}

void QtMonthYearSelector::onMonthChange(const QString& text)
{
    edit->setText(QString::number(months.indexOf(text)) +"/" + QString::number(year->value()));
}


void QtMonthYearSelector::onYearChange(const int& year)
{
    edit->setText(QString::number(months.indexOf(month->currentText())) +"/" + QString::number(year));
}


