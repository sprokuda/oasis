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
    
    startDateLabel = new QLabel("Start Date",this);
    selectorStart = new QtMonthYearSelector(this);
    QHBoxLayout* startDateLayout = new QHBoxLayout;
    startDateLayout->setContentsMargins(1, 1, 1, 1);
    startDateLayout->addStretch();
    startDateLayout->addWidget(startDateLabel);
    startDateLayout->addWidget(selectorStart);

    endDateLabel = new QLabel("End Date",this);
    selectorEnd = new QtMonthYearSelector(this);
    QHBoxLayout* endDateLayout = new QHBoxLayout;
    endDateLayout->setContentsMargins(1, 1, 1, 1);
    endDateLayout->addStretch();
    endDateLayout->addWidget(endDateLabel);
    endDateLayout->addWidget(selectorEnd);

    pickerLabel = new QLabel("Calendar picker (DEMO)", this);
    picker = new QtDatePicker();
    QHBoxLayout* pickerLayout = new QHBoxLayout;
//    pickerLayout->setContentsMargins(10, 10, 10, 10);
    pickerLayout->addStretch();
    pickerLayout->addWidget(pickerLabel);
    pickerLayout->addWidget(picker);


    prodColLabel = new QLabel("Production Colums", this);
    prodCol = new QComboBox(this);
    prodCol->addItems({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"});
    QHBoxLayout* prodColLayout = new QHBoxLayout;
    prodColLayout->setContentsMargins(10, 10, 10, 10);
    prodColLayout->addStretch();
    prodColLayout->addWidget(prodColLabel);
    prodColLayout->addWidget(prodCol);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(logoLayout);
    mainLayout->addLayout(startDateLayout);
    mainLayout->addLayout(endDateLayout);
    mainLayout->addLayout(pickerLayout);
    mainLayout->addLayout(prodColLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
    setWindowTitle(tr("Data Extractor"));

    this->setFont(*buttonFont);
//    this->resize(mainWidth, mainHeight);

}


//void PGC::onShowWS()
//{
//    sp->show();
//    sp->adjustPosition();
//}

void PGC::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);
    this->picker->adjustPopupPosition();
//    this->multiSelect->adjustPopupPosition();
//    this->sp->adjustPosition();

}

void PGC::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    this->picker->adjustPopupPosition();
//    this->multiSelect->adjustPopupPosition();
//    this->sp->adjustPosition();

}
