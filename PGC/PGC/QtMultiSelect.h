#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QDate>

#include "QtMultiSelectPopup.h"


class QtMultiSelect : public QWidget
{
    Q_OBJECT

public:
    QtMultiSelect(QWidget* parent = Q_NULLPTR);

    void adjustPopupPosition();
    QtMultiSelectPopup& getPopup() { return *popup; };
    QString getText();
public slots:

private slots:
    void onShowPopupButtonClicked();
    void onAddItem(const QString& item_text);
    void onRemoveItem(const QString& item_text);
    void onClickCatch(int value);
signals:
    void editingFinished();
private:

    QtMultiSelectPopup* popup;
    QLineEdit* edit;
    QToolButton* button;

    QFont font;

    QHBoxLayout* ctrlLayout;

    bool eventFilter(QObject* object, QEvent* event);

};

