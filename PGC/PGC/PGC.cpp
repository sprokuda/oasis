#include "PGC.h"

QString workingDirectory;

PGC::PGC(QWidget *parent)
    : QWidget(parent)
{
    buttonFont = new QFont("Calibri", 11, QFont::Medium);
    smallFont = new QFont("Calibri", 8, QFont::Medium);
    bigFont = new QFont("Calibri", 14, QFont::Medium);

    companyLogoQLabel = new QLabel(this);
    QPixmap logo = QPixmap(workingDirectory + "\\centaur-logo.png").scaled({ 100,36 }, Qt::KeepAspectRatioByExpanding);
    companyLogoQLabel->setPixmap(logo);

    programLogoQLineEdit = new QLineEdit(this);
    programLogoQLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    programLogoQLineEdit->setEnabled(false);
    programLogoQLineEdit->setFixedHeight(36); //logo image height
    programLogoQLineEdit->setFixedWidth(220);
    programLogoQLineEdit->setFont(*bigFont);

    programLogoQLineEdit->setText("OASIS PGC Data Extractor");

    QHBoxLayout* logoLayout = new QHBoxLayout;
    logoLayout->addStretch();
    logoLayout->addWidget(companyLogoQLabel);
    logoLayout->addWidget(programLogoQLineEdit);
    
    startDateLabel = new QLabel("Start Date");
    selectorStart = new QtMonthYearSelector(this);
    QHBoxLayout* startDateLayout = new QHBoxLayout;
    startDateLayout->addStretch();
    startDateLayout->addWidget(startDateLabel);
    startDateLayout->addWidget(selectorStart);

    endDateLabel = new QLabel("End Date");
    selectorEnd = new QtMonthYearSelector(this);
    QHBoxLayout* endDateLayout = new QHBoxLayout;
    endDateLayout->addStretch();
    endDateLayout->addWidget(endDateLabel);
    endDateLayout->addWidget(selectorEnd);






    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(logoLayout);
    mainLayout->addLayout(startDateLayout);
    mainLayout->addLayout(endDateLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Data Extractor"));

    this->setFont(*buttonFont);
//    this->resize(mainWidth, mainHeight);

}
