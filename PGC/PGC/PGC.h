#pragma once

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout.h>
#include <QDateEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QTextBrowser>

#include <Qthread>

#include "QtMonthYearSelector.h"
#include "QtDatePicker.h"
#include "QtMultiSelect.h"
#include "QtWaitingSpinner.h"

#include "dbHandler.h"

class PGC : public QWidget
{
    Q_OBJECT

public:
    PGC(QWidget *parent = Q_NULLPTR);
    ~PGC();
    void initialLoad();

public slots:
    void onAllCompleted();
    void updateLog(QString message);
    void onQueryAppBook(QStringList list);

private:
    QLabel* companyLogoQLabel;
    QLineEdit* programLogoQLineEdit;

    QLabel* startDateLabel;
    QtDatePicker* pickerStart;
    QHBoxLayout* startDateLayout;

    QLabel* endDateLabel;
    QtDatePicker* pickerEnd;
    QHBoxLayout* endDateLayout;


    QLabel* prodColLabel;
    QComboBox* prodCol;
    QHBoxLayout* prodColLayout;

    QLabel* incBooks;
    QtMultiSelect* booksSelect;
    QHBoxLayout* booksLayout;

    QLabel* practiceNameLabel;
    QLineEdit* practiceName;
    QHBoxLayout* practiceLayout;

    QPushButton* exctractButton;
    QPushButton* exitAppButton;
    QHBoxLayout* buttonLayout;

    QTextBrowser* log;

    QFont* buttonFont;
    QFont* smallFont;
    QFont* bigFont;

    size_t buttonWidth = 170;
    size_t buttonHeight = 30;

    size_t mainWidth = 600;
    size_t mainHeight = 600;

    QtWaitingSpinner* spinner;
    dbHandler* handler;
    QThread* thread;

    void exctractData();
    bool checkBeforeExtract();
    QString convertDateForMimer(const QString date);
    void exitProgram();


    void moveEvent(QMoveEvent* event);
    void resizeEvent(QResizeEvent* event);


};
