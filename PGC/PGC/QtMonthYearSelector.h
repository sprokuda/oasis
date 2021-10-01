#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDate>
#include <QLayout>



class QtMonthYearSelector : public QWidget
{
    Q_OBJECT

public:
    QtMonthYearSelector(QWidget* parent = Q_NULLPTR);



public slots:

private slots:

    void onMonthChange(const QString& text);
    void onYearChange(const int& year);

signals:


private:
    QStringList months = { "January","Febuary","March","April","May","June","July","August","September","October","November","December" };

    QLineEdit* edit;
    QComboBox* month;
    QSpinBox* year;


};
