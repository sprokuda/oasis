#pragma once
#include <QtWidgets/QWidget>
#include <QLayout.h>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QStringList>
#include <QCheckBox>

#include <QDesktopWidget>
#include <QApplication>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

class QtMultiSelectPopup : public QWidget//QFrame
{
    Q_OBJECT

public:
    QtMultiSelectPopup(QWidget* parent = Q_NULLPTR);
    ~QtMultiSelectPopup();
    void setTable(const QStringList& list);

signals:
    void addItem(const QString& text);
    void removeItem(const QString& text);
    void clickCatched(int value);
    void editingFinished();
private:

    QVBoxLayout* mainLayout;
    QList<QHBoxLayout*> layout_list;
    QList<QLineEdit*> edit_list;

    void paintEvent(QPaintEvent* event);
    bool eventFilter(QObject* object, QEvent* event);

private slots:

    void selectItem(bool state, const QString& item_text);

    void addDummyItem(const int state);
};

