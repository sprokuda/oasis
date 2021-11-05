#include "logOfPGC.h"
#include <QAbstractButton>
#include <QPushButton>

void logOfPGC::openLog()
{
    const char* oasis_dir_name = "OASIS";
    const char* pgc_dir_name = "PGC";
    const char* log_dir_name = "Log";

    QDir dir;
    dir.cd("C:/");
    if (!QDir(oasis_dir_name).exists()) qDebug() << dir.mkdir(oasis_dir_name);
    dir.cd(oasis_dir_name);

    if (!QDir(pgc_dir_name).exists()) qDebug() << dir.mkdir(pgc_dir_name);
    dir.cd(pgc_dir_name);

    if (!QDir(log_dir_name).exists()) qDebug() << dir.mkdir(log_dir_name);
    dir.cd(log_dir_name);

    const QFileInfo outputDir(dir.absolutePath());
    if ((!outputDir.exists()) || (!outputDir.isDir()) || (!outputDir.isWritable()))
    {
        QMessageBox::warning(nullptr, 0, "Output directory problem", "output directory does not exist,\nis not a directory,\nor is not writeable");
    }
    QString file_name = dir.absolutePath() + "\\" + QDate::currentDate().toString("yyyyMMdd") + "_" + QTime::currentTime().toString("hh-mm-ss-zzz") + QString(".log");

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
	if(str != QString("\n")) 	log << str.toStdString(); 
}