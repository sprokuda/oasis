#pragma once
#include <qobject.h>

class csvWriter : public QObject
{
    Q_OBJECT
public:
    explicit csvWriter(QObject* parent = nullptr);
    ~csvWriter();


}

