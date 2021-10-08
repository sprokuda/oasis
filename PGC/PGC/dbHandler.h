#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <iostream>

//#include "dbScripts.h"

class dbHandler : public QObject
{
    Q_OBJECT
public:
    explicit dbHandler(QObject* parent = nullptr);
    ~dbHandler();

    Q_INVOKABLE void doQueries();
    Q_INVOKABLE void queryAppBook();
    Q_INVOKABLE void loadBooksAndFunctions();
    QSqlDatabase db;

signals:
    void allCompleted();
    void appBookReady(QStringList list);

};

