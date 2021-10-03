#pragma once

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
    QtPassword(const QFont& qfont, const int& bHeight, QWidget* parent = Q_NULLPTR);

private:
    QFont font;
    int buttonHeight;
    QLabel* label;
    QLineEdit* edit;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QMessageBox* box;

signals:
    void passwordAccepted();
    void passwordRejected();

private slots:

    void onPasswordEntered();
    void onCancelClicked();

};

