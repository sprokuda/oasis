#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDate>

#include "QtMultiSelectPopup.h"


class QtMultiSelect : public QWidget
{
    Q_OBJECT

public:
    QtMultiSelect(const QFont& qfont, const int& bHeight, QWidget* parent = Q_NULLPTR);

    void adjustPopupPosition();
    QtMultiSelectPopup& getPopup() { return *popup; };

public slots:


private slots:
    void onShowPopupButtonClicked();
    void onAddItem(const QString& item_text);
    void onRemoveItem(const QString& item_text);
signals:

private:

    QtMultiSelectPopup* popup;
    QLineEdit* edit;
    QPushButton* showPP;

    QFont font;
    int buttonHeight;

    QHBoxLayout* ctrlLayout;

};

