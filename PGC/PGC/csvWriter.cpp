#include "csvWriter.h"



using namespace std;

csvWriter::csvWriter(QObject* parent) : QObject(parent)
{
    const char* oasis_dir_name = "OASIS";
    const char* pgc_dir_name = "PGC";

    QDir dir;
    dir.cd("C:/");

    auto create_and_report = [&dir](QString dir_name)
    {
        auto result = dir.mkdir(dir_name);
        if (result) return QString(dir_name) + QString(" is created");
        else return QString(dir_name) + QString(" directory can't be created or already exists");
    };

    auto check_directory = [&dir, create_and_report](QString dir_name)
    {
        bool fld_report = QDir(dir_name).exists();
        if (!fld_report)
        {
            cout << create_and_report(dir_name).toStdString() + "\n";
        }
        auto cd_report = dir.cd(dir_name);
        if (!cd_report)
        {
            cout <<  (string("Can't enter directory ") + string("\"dir_name\"\n"));
        }
    };


    check_directory(oasis_dir_name);
    check_directory(pgc_dir_name);

    const QFileInfo outputDir(dir.absolutePath());
    if ((!outputDir.exists()) || (!outputDir.isDir()) || (!outputDir.isWritable()))
    {
        cout << "output directory does not exist, is not a directory, or is not writeable" << endl;
    }

    QString fileName = QDate::currentDate().toString("yyyyMMdd") + "_" + QTime::currentTime().toString("hh-mm-ss-zzz") + QString(".csv");
    cout << (dir.absolutePath() + "\\" + fileName).toStdString() << endl;
    fflush(stdout);

    file = new QFile(dir.absolutePath() + "\\" + fileName);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file->close();
    }

}

csvWriter::~csvWriter()
{
    if (file->isOpen()) 
    {
        file->close();
    }
}




