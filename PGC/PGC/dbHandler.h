#pragma once

//#include <QObject>
//#include <QSqlDatabase>
//#include <QSqlQuery>
//#include <QSqlRecord>
//#include <QSqlError>
#include <QVariant>
#include <iostream>

class dbHandler : public QObject
{
    Q_OBJECT
public:
    explicit dbHandler(QObject* parent = nullptr);

    Q_INVOKABLE void doQueries();

signals:
    void allCompleted();

};

