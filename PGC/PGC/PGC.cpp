#include "PGC.h"

extern QString workingDirectory;

PGC::PGC(QWidget *parent)
    : QWidget(parent)
{
    buttonFont = new QFont("Calibri", 10, QFont::Medium);
    smallFont = new QFont("Calibri", 8, QFont::Medium);
    bigFont = new QFont("Calibri", 12, QFont::Medium);

    companyLogoQLabel = new QLabel(this);
    QPixmap logo = QPixmap(workingDirectory + "\\centaur-logo.png").scaled({ 100,36 }, Qt::KeepAspectRatioByExpanding);
    companyLogoQLabel->setPixmap(logo);

    programLogoQLineEdit = new QLineEdit(this);
//    programLogoQLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    programLogoQLineEdit->setEnabled(false);
    programLogoQLineEdit->setFixedHeight(36); //logo image height
    programLogoQLineEdit->setFixedWidth(180);
    programLogoQLineEdit->setFont(*bigFont);

    programLogoQLineEdit->setText("OASIS PGC Data Extractor");
    programLogoQLineEdit->setAlignment(Qt::AlignCenter);

    QHBoxLayout* logoLayout = new QHBoxLayout();
    logoLayout->addStretch();
    logoLayout->setContentsMargins(10, 10, 10, 10);
    logoLayout->addWidget(companyLogoQLabel);
    logoLayout->addWidget(programLogoQLineEdit);
    
    startDateLabel = new QLabel("Start Date",this);
    selectorStart = new QtMonthYearSelector(this);
    QHBoxLayout* startDateLayout = new QHBoxLayout();
    startDateLayout->setContentsMargins(1, 1, 1, 1);
    startDateLayout->addStretch();
    startDateLayout->addWidget(startDateLabel);
    startDateLayout->addWidget(selectorStart);

    endDateLabel = new QLabel("End Date",this);
    selectorEnd = new QtMonthYearSelector(this);
    QHBoxLayout* endDateLayout = new QHBoxLayout();
    endDateLayout->setContentsMargins(1, 1, 1, 1);
    endDateLayout->addStretch();
    endDateLayout->addWidget(endDateLabel);
    endDateLayout->addWidget(selectorEnd);

    pickerLabel = new QLabel("Calendar picker \n(DEMO)", this);
    picker = new QtDatePicker();
    QHBoxLayout* pickerLayout = new QHBoxLayout();
//    pickerLayout->setContentsMargins(10, 10, 10, 10);
    pickerLayout->addStretch();
    pickerLayout->addWidget(pickerLabel);
    pickerLayout->addWidget(picker);


    prodColLabel = new QLabel("Production Colums", this);
    prodCol = new QComboBox(this);
    prodCol->addItems({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"});
    QHBoxLayout* prodColLayout = new QHBoxLayout();
    prodColLayout->setContentsMargins(10, 10, 10, 10);
    prodColLayout->addStretch();
    prodColLayout->addWidget(prodColLabel);
    prodColLayout->addWidget(prodCol);

    incBooks = new QLabel("Include \nAppointment Books", this);
    booksSelect = new QtMultiSelect(*buttonFont, 26);
    QStringList books = { "0001","0002","0005" };
    booksSelect->getPopup().setTable(books);
    QHBoxLayout* booksLayout = new QHBoxLayout();
//    endDateLayout->setContentsMargins(1, 1, 1, 1);
    booksLayout->addStretch();
    booksLayout->addWidget(incBooks);
    booksLayout->addWidget(booksSelect);


    practiceNameLabel = new QLabel("Practice Name", this);
    practiceName = new QLineEdit(this);

    QHBoxLayout* practiceLayout = new QHBoxLayout();
    practiceLayout->setContentsMargins(10, 10, 10, 10);
    practiceLayout->addStretch();
    practiceLayout->addWidget(practiceNameLabel);
    practiceLayout->addWidget(practiceName);

    exctractButton = new QPushButton("Exctract");
    exctractButton->setFixedSize(72, buttonHeight*1.2);
    connect(exctractButton, &QPushButton::clicked, this, &PGC::exctractData);

    exitAppButton = new QPushButton("Cancel");
    exitAppButton->setFixedSize(72, buttonHeight * 1.2);
    connect(exitAppButton, &QPushButton::clicked, this, &PGC::exitProgram);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(10, 10, 10, 10);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exctractButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exitAppButton);
    buttonLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(logoLayout);
    mainLayout->addLayout(startDateLayout);
    mainLayout->addLayout(endDateLayout);
    mainLayout->addLayout(pickerLayout);
    mainLayout->addLayout(prodColLayout);
    mainLayout->addLayout(booksLayout);
    mainLayout->addLayout(practiceLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
    setWindowTitle(tr("Data Extractor"));

    this->setFont(*buttonFont);
//    this->resize(mainWidth, mainHeight);

    spinner = new QtWaitingSpinner(this);
    handler = new dbHandler();

    thread = new QThread();

    handler->moveToThread(thread);
    connect(handler, SIGNAL(allCompleted()), this, SLOT(onAllCompleted()));
    thread->start();

//    connect(handler, SIGNAL(allCompleted()),this, SLOT(onAllCompleted()));

}

PGC::~PGC() 
{
    thread->deleteLater();
    delete handler;
//    delete thread;
    delete booksSelect;
    delete picker;
}

void PGC::exctractData()
{
    /* all querying routines are call from here*/
    spinner->show();
    spinner->adjustPosition();

    QMetaObject::invokeMethod(handler, "doQueries",
        Qt::QueuedConnection
//                Qt::DirectConnection,
//        Q_ARG(QString, aligner_file_path),
//        Q_ARG(QString, patchFilePath),
//        Q_ARG(QString, patched_file_path)
    );
}

void PGC::onAllCompleted()
{
    spinner->hide();
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
    this->booksSelect->adjustPopupPosition();
    this->spinner->adjustPosition();

}

void PGC::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    this->picker->adjustPopupPosition();
    this->booksSelect->adjustPopupPosition();
    this->spinner->adjustPosition();

}


void PGC::exitProgram()
{
    spinner->hide();
    QMessageBox msgBox(this);
    msgBox.setText("Conform you want to exit program");
    msgBox.setIcon(QMessageBox::Warning);
    auto* ok = msgBox.addButton("Exit Program", QMessageBox::ActionRole);
    auto* cancel = msgBox.addButton(QMessageBox::Cancel);

    msgBox.setFont(*buttonFont);

    msgBox.exec();

    if (msgBox.clickedButton() == ok)
    {
        qApp->quit();
    }
    else if (msgBox.clickedButton() == cancel)
    {
        return;
    }

}
