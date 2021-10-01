#pragma once

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout.h>
#include <QDateEdit>
#include <QPushButton>
#include <QComboBox>

#include "QtMonthYearSelector.h"
#include "QtDatePicker.h"

class PGC : public QWidget
{
    Q_OBJECT

public:
    PGC(QWidget *parent = Q_NULLPTR);


private:
    QLabel* companyLogoQLabel;
    QLineEdit* programLogoQLineEdit;

    QLabel* startDateLabel;
    QtMonthYearSelector* selectorStart;

    QLabel* endDateLabel;
    QtMonthYearSelector* selectorEnd;

    QLabel* pickerLabel;
    QtDatePicker* picker;


    QLabel* prodColLabel;
    QComboBox* prodCol;


    QFont* buttonFont;
    QFont* smallFont;
    QFont* bigFont;

    size_t buttonWidth = 170;
    size_t buttonHeight = 30;

    size_t mainWidth = 600;
    size_t mainHeight = 600;

    void moveEvent(QMoveEvent* event);
    void resizeEvent(QResizeEvent* event);


};
