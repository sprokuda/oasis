#pragma once

#include <QWidget>
#include <QLabel>
#include <QlineEdit>
#include <QPushButton>
#include <QDate>

#include "QtDatePickerPopup.h"


class QtDatePicker : public QWidget
{
    Q_OBJECT

public:
    QtDatePicker(QWidget* parent = Q_NULLPTR);

    void adjustPopupPosition();

public slots:

private slots:
    void onShowPopupButtonClicked();
    void setDate(QDate date);
signals:

    void editingFinished();

private:

    QtDatePickerPopup* popup;
    QLabel* dateLbl;
    QLineEdit* edit;
    QPushButton* showPP;

    bool eventFilter(QObject* object, QEvent* event);
};

