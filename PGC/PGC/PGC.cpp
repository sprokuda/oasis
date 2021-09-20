#include "PGC.h"

QString workingDirectory;

PGC::PGC(QWidget *parent)
    : QWidget(parent)
{
    buttonFont = new QFont("Calibri", 9, QFont::Medium);
    smallFont = new QFont("Calibri", 8, QFont::Medium);
    bigFont = new QFont("Calibri", 16, QFont::Medium);

    companyLogoQLabel = new QLabel(this);
    companyLogoQLabel->setPixmap(QPixmap(workingDirectory + "\\centaur-logo.png"));

    programLogoQLineEdit = new QLineEdit(this);
    programLogoQLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    programLogoQLineEdit->setEnabled(false);
    programLogoQLineEdit->setFixedHeight(58); //logo image height
    programLogoQLineEdit->setFixedWidth(360);
    programLogoQLineEdit->setFont(*bigFont);

    programLogoQLineEdit->setText("OASIS PGC Data Extractor");

    QHBoxLayout* logoLayout = new QHBoxLayout;
    logoLayout->addStretch();
    logoLayout->addWidget(companyLogoQLabel);
    logoLayout->addWidget(programLogoQLineEdit);
    
    startQLabel = new QLabel("Start Date");
    startQDateEdit = new QDateEdit;

    QPushButton* b1 = new QPushButton("PickDate",this);
    QWidget* clndrWdgt = new QWidget();
    QVBoxLayout* clndrLayout = new QVBoxLayout(clndrWdgt);
    QCalendarWidget* startDateQCalWdgt1 = new QCalendarWidget(clndrWdgt);
    clndrLayout->addWidget(startDateQCalWdgt1);
    clndrWdgt->setLayout(clndrLayout);

    connect(b1, SIGNAL(clicked()), clndrWdgt, SLOT(show()));

    QHBoxLayout* startDateLayout = new QHBoxLayout;
    startDateLayout->addStretch();
    startDateLayout->addWidget(startQLabel);
    startDateLayout->addWidget(startQDateEdit);
    startDateLayout->addWidget(b1);


    //endDateQLabel = new QLabel("End Date:",this);
    //endDateQCombo = new QComboBox(this);
    //endDateQCalWdgt = new QCalendarWidget(this);

    //QHBoxLayout* endDateLayout = new QHBoxLayout;
    //endDateLayout->addStretch();
    //endDateLayout->addWidget(endDateQLabel);
    //endDateLayout->addWidget(endDateQCalWdgt);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(logoLayout);
    mainLayout->addLayout(startDateLayout);
//    mainLayout->addLayout(endDateLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Data Extractor"));


    this->resize(mainWidth, mainHeight);

}
