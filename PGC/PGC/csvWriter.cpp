#include "csvWriter.h"



using namespace std;

csvWriter::csvWriter(QObject* parent) : QObject(parent)
{
    const char* dir1 = "OASIS";
    const char* dir2 = "PGC";
    
    QDir dir;
    dir.cd("C:/");

    if (!QDir(dir1).exists())
        cout << "QDir returned: " << dir.mkdir(dir1) << endl;
    dir.cd(dir1);

    const QFileInfo outputDir1(dir.absolutePath().toStdString().c_str());
    if ((!outputDir1.exists()) || (!outputDir1.isDir()) || (!outputDir1.isWritable())) 
    {
        cout << "output directory does not exist, is not a directory, or is not writeable"
            << "\t" << outputDir1.absoluteFilePath().toStdString() << endl;
    }

    if (!QDir(dir2).exists())
        cout << "QDir returned: " << dir.mkdir(dir2) << endl;
    dir.cd(dir2);

    const QFileInfo outputDir2(dir.absolutePath().toStdString().c_str());
    if ((!outputDir2.exists()) || (!outputDir2.isDir()) || (!outputDir2.isWritable()))
    {
        cout << "output directory does not exist, is not a directory, or is not writeable"
            << "\t" << outputDir2.absoluteFilePath().toStdString() << endl;
    }

    QString fileName = QDate::currentDate().toString("yyyyMMdd") + "_" + QTime::currentTime().toString("hh-mm-ss-zzz") + QString(".csv");
    cout << (dir.absolutePath() + "\\" + fileName).toStdString() << endl;
    fflush(stdout);

    file = new QFile(dir.absolutePath() + "\\" + fileName);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file->close();
    }

    //else {
    //    file.write(logTextEdit->toPlainText().toUtf8());
    //    file.close();
    //}

    //QFile file(outputDir_ + "/" + fileName);
    //if (!file.open(QFile::WriteOnly))
    //{
    //    QMessageBox::warning(0, "Could not create Project File",
    //        QObject::tr("\n Could not create Project File on disk"));

    //    return false;
    //}
}

csvWriter::~csvWriter()
{
    if (file->isOpen()) 
    {
        file->close();
    }
}

//template<typename T>
//void csvWriter::writeArray(vector<T> array)
//{
//
////    file->write(data);
//}



