#pragma once

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QTextStream>
#include <iostream>
#include <vector>

using namespace std;

class csvWriter : public QObject
{
    Q_OBJECT
public:
    explicit csvWriter(QObject* parent = nullptr);
    ~csvWriter();

    template<typename T>
    void writeArray(const QString& header, vector<T> data)
    {
        QTextStream out(file);
        out << header;
        out << ",";
        for (auto it = data.begin(); it != data.end(); it++)
        {
            out << ",";
            out << *it;
        }
        out << "\n";
    };

    void csvWriter::writeMonthly(const QString& header, const QStringList& data);

private:
    QFile* file;

};

