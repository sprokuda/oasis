#pragma once

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout.h>
#include <QDateEdit>
#include <QPushButton>
#include <QCalendarWidget>

class PGC : public QWidget
{
    Q_OBJECT

public:
    PGC(QWidget *parent = Q_NULLPTR);


private:
    QLabel* companyLogoQLabel;
    QLineEdit* programLogoQLineEdit;

    QLabel* startQLabel;
    QDateEdit* startQDateEdit;


    QLabel* endDateQLabel;


    QFont* buttonFont;
    QFont* smallFont;
    QFont* bigFont;

    size_t buttonWidth = 170;
    size_t buttonHeight = 30;

    size_t mainWidth = 600;
    size_t mainHeight = 600;


};
