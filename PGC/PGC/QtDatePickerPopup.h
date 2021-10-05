#pragma once
#include <QtWidgets/QWidget>
#include <QLayout.h>
#include <QCalendarWidget>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QDate>

#include <QDesktopWidget>
#include <QApplication>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

class QtDatePickerPopup : public QWidget
{
    Q_OBJECT

public:
    QtDatePickerPopup(QWidget* parent = Q_NULLPTR);
    void setDate(const QString& text);
signals:
    void dateSelected(const QDate& date);
//    void datePeriodSelected(const QDate& begin, const QDate& end);

private:

    QCalendarWidget* cndrWidget;
    QLabel* label;
//    QPushButton* hideButton;
    void paintEvent(QPaintEvent* event);

private slots:
    void onCalendarDateSelected(const QDate& date);
};

