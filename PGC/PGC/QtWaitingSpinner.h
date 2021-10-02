#pragma once
#include <QtWidgets/QWidget>
#include <QLabel>

#include <QDesktopWidget>
#include <QApplication>


class QtWaitingSpinner : public QWidget
{
    Q_OBJECT

public:
    QtWaitingSpinner(QWidget* parent = Q_NULLPTR);

    void adjustPosition();
signals:

private:

    QLabel* label;

private slots:

};

