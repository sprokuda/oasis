#pragma once
#include <QtWidgets/QWidget>
#include <QLayout.h>
#include <QCalendarWidget>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QDate>
#include <QTableView>

#include <QDesktopWidget>
#include <QApplication>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

#include <QThread>

#include "callDelay.h"

class QtDatePickerPopup : public QWidget
{
    Q_OBJECT

public:
    QtDatePickerPopup(QWidget* parent = Q_NULLPTR);
    ~QtDatePickerPopup();
    void setDate(const QString& text);
public slots:
    void onTodayButton();

signals:
    void dateSelected(const QDate& date);
//    void datePeriodSelected(const QDate& begin, const QDate& end);

private:

    QCalendarWidget* calendar;
    QLabel* label;
    QToolButton* todayButton;
    void paintEvent(QPaintEvent* event);

    QThread* thread;
    callDelay* delay;

private slots:
    void onCalendarDateSelected(const QDate& date);
    void onDelayFinished();
};

