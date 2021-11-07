#include "logOfPGC.h"
#include <QAbstractButton>
#include <QPushButton>

extern QString initial_log;


void logOfPGC::openLog()
{
    const char* oasis_dir_name = "OASIS1";
    const char* pgc_dir_name = "PGC1";
    const char* log_dir_name = "Log1";

    QDir dir;
    if (!dir.cd("C:/"))
    {
        initial_log += QString("There is no drive C:\\\n");
        return;
    }

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
            initial_log += create_and_report(dir_name) + "\n";
        }
        auto cd_report = dir.cd(dir_name);
        if (!cd_report)
        {
            initial_log += (QString("Cann't enter directory ") + QString("\"dir_name\"\n"));
            QMessageBox::warning(nullptr, 0, "Output directory problem", "output directory "+ QString(dir_name) + " does not exist, \nis not a directory, \nor is not writeable");
        }

    };


    check_directory(oasis_dir_name);
    check_directory(pgc_dir_name);
    check_directory(log_dir_name);

    const QFileInfo outputDir(dir.absolutePath());
    if ((!outputDir.exists()) || (!outputDir.isDir()) || (!outputDir.isWritable()))
    {
        QMessageBox::warning(nullptr, 0, "Output directory problem", "output directory does not exist,\nis not a directory,\nor is not writeable");
    }
    QString file_name = dir.absolutePath() + "\\" + QDate::currentDate().toString("yyyyMMdd") + "_" + QTime::currentTime().toString("hh-mm-ss-zzz") + QString(".log");
    //initial_log += "Log is being saved to : " + dir.absolutePath() + "\n";
    initial_log += "Log file is: " + file_name.replace("/","\\") + "\n";
    log.open(file_name.toStdString());

tryOpenLog:
    if (!log.is_open())
    {
        QMessageBox msgBox(nullptr);
        msgBox.setText("Log file can not be created");
        msgBox.setIcon(QMessageBox::Warning);
        auto* open = msgBox.addButton("Try to open again", QMessageBox::ActionRole);
        auto* exit = msgBox.addButton("Exit Program", QMessageBox::ActionRole);

        msgBox.exec();

        if (msgBox.clickedButton() == open)
        {
            log.open(file_name.toStdString()); goto tryOpenLog;
        }
        else if (msgBox.clickedButton() == exit)
        {
            emit noLogFileOpended();
        }
    }
    else
    {
        emit logFileOpened();
    }
};




void logOfPGC::appendString(QString str)
{ 
	//if(str != QString("\n")) 	
    log << str.toStdString() << "\n";
}