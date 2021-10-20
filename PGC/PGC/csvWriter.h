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

    void writeArray(const QString& header, vector<pair<QString,QString>> data)
    {
        QTextStream out(file);
        out << header;
        out << ",";
        for (auto it = data.begin(); it != data.end(); it++)
        {
            out << ",";
            out << it->first <<"\t" << it->second;
        }
        out << "\n";
    };

    void writeHeader(const vector<QString>& data)
    {
        QTextStream out(file);
        out << "Headers";
        out << ",Snapshot";
        for (auto it = data.begin(); it != data.end(); it++)
        {
            out << ",";
            out << *it;
        }
        out << "\n";
    };



private:
    QFile* file;

};

