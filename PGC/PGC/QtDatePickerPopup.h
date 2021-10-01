#pragma once
#include <QtWidgets/QWidget>
#include <QLayout.h>
#include <QCalendarWidget>
#include <QPushButton>
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

signals:
    void dateSelected(const QDate& date);
//    void datePeriodSelected(const QDate& begin, const QDate& end);

private:

    QCalendarWidget* cndrWidget;
    QPushButton* hideButton;
    void paintEvent(QPaintEvent* event);
//    void resizeEvent(QResizeEvent* event);
//    void moveEvent(QMoveEvent* event);

private slots:
    void onCalendarDateSelected(const QDate& date);
};

