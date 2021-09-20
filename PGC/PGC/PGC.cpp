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




    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(logoLayout);


    setLayout(mainLayout);
    setWindowTitle(tr("Data Extractor"));


    this->resize(mainWidth, mainHeight);

}
