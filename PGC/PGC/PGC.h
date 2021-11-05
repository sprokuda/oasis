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
#include <QFont>

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
    void onDbconnectError(QString message);
    void onDbSuccessful();
    void updateLog(QString message);
    void onQueryAppBook(map<string, string> books);
    void onExtractionCompleted();

private:
    QFont workingFont;

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

    map<string, string> m_books;


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
