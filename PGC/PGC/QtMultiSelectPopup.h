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
    QtMultiSelectPopup(const QFont& qfont, const int& bHeight, QWidget* parent = Q_NULLPTR);
    void setTable(const QStringList& lst);
    int width();

signals:
    void addItem(const QString& text);
    void removeItem(const QString& text);

private:

    int edit_width;
    int check_width;
    int header_width;
    int total_width;

    QTableWidget* table;
//    QPushButton* hideButton;
    QFont font;
    int buttonHeight;

    void paintEvent(QPaintEvent* event);

private slots:

    void selectItem(bool state, const QString& item_text);

    void addDummyItem(const int state);
};

