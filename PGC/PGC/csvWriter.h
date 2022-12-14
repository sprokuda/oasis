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
    void writeArray(const QString& header, vector<T> data, QString prefix = QString::QString(""), QString postfix = QString::QString(""))
    {
        QTextStream out(file);
        out << header;
        out << ",";
        for (auto it = data.begin(); it != data.end(); it++)
        {
            out << ",";
            out << prefix;
            out << *it;
            out << postfix;
        }
        out << "\n";
    };

    template<typename T>
    void writeSnapshot(const QString& header, T data, QString prefix = QString::QString(""), QString postfix = QString::QString(""))
    {
        QTextStream out(file);
        out << header;
        out << ",";

        out << prefix;
        out << data;
        out << postfix;

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

    template<typename T1, typename T2>
    void writeTop10(const QString& header, vector<pair<T1,T2>> data, QString prefix = QString::QString(""), QString postfix = QString::QString(""))
    {
        QTextStream out(file);
        int i = 1;
        out << header <<"\n";

        for (auto it = data.begin(); it != data.end(); it++)
        {
            out << i << "," << it->first << ","<< prefix << it->second << "\n";
            i++;
            if (i == 11) break;
        }
    };


    QFile* getFilePtr() { return file; }


    template <typename T>
    QTextStream& operator << ( const T& value)
    {
        QTextStream out1(file);
        return out1 << value;
    };

private:
    QFile* file;
    unique_ptr<QTextStream> out_ptr;
};

