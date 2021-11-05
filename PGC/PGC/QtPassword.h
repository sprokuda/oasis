#pragma once
#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDate>
#include <QLayout>
#include <QKeyEvent>

class QtPassword : public QWidget
{
    Q_OBJECT

public:
    QtPassword(const QFont& qfont, QWidget* parent = Q_NULLPTR);

private:
    QFont font;
    QLabel* label;
    QLineEdit* edit;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QMessageBox* box;
    QDate today;
    QString password;
    bool if_first_time = true;
signals:
    void passwordAccepted();
    void passwordRejected();

private slots:

    void onPasswordEntered();
    void onCancelClicked();
};

