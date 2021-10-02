#pragma once

#include <QObject>
//#include <QTest>
#include <chrono>

class dbHandler : public QObject
{
    Q_OBJECT
public:
    explicit dbHandler(QObject* parent = nullptr);

    Q_INVOKABLE void doQueries();

signals:
    void allCompleted();

};

