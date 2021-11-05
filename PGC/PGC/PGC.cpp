#include "PGC.h"


PGC::PGC(QWidget *parent)
    : QWidget(parent)
{
    workingFont = QFont("Calibri", 10);
    this->setFont(workingFont);
    
    startDateLabel = new QLabel("Start Date",this);
    pickerStart = new QtDatePicker(this);
    pickerStart->setDate(QDate(2020, 1, 1));
    startDateLayout = new QHBoxLayout();
//    startDateLayout->setContentsMargins(1, 1, 1, 1);
    startDateLayout->addStretch();
    startDateLayout->addWidget(startDateLabel);
    startDateLayout->addWidget(pickerStart);

    endDateLabel = new QLabel("End Date",this);
    pickerEnd = new QtDatePicker(this);
    pickerEnd->setDate(QDate(2020, 12, 31));
    endDateLayout = new QHBoxLayout();
//    endDateLayout->setContentsMargins(1, 1, 1, 1);
    endDateLayout->addStretch();
    endDateLayout->addWidget(endDateLabel);
    endDateLayout->addWidget(pickerEnd);

    prodColLabel = new QLabel("Production Colums", this);
    prodCol = new QComboBox(this);
    prodCol->addItems({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"});
    prodColLayout = new QHBoxLayout();
//    prodColLayout->setContentsMargins(10, 10, 10, 10);
    prodColLayout->addStretch();
    prodColLayout->addWidget(prodColLabel);
    prodColLayout->addWidget(prodCol);

    incBooks = new QLabel("Include\nAppointment\nBooks", this);
    booksSelect = new QtMultiSelect(this);
//    QStringList books = { "book1","book2","book3","book4"};
//    booksSelect->getPopup().setTable(books);
//    booksSelect->selectAllBooks();
    booksLayout = new QHBoxLayout();
//    endDateLayout->setContentsMargins(1, 1, 1, 1);
    booksLayout->addStretch();
    booksLayout->addWidget(incBooks);
    booksLayout->addWidget(booksSelect);


    practiceNameLabel = new QLabel("Practice Name", this);
    practiceName = new QLineEdit(this);
    practiceName->setText("Dental Surgery");

    practiceLayout = new QHBoxLayout();
//    practiceLayout->setContentsMargins(10, 10, 10, 10);
    practiceLayout->addStretch();
    practiceLayout->addWidget(practiceNameLabel);
    practiceLayout->addWidget(practiceName);

    exctractButton = new QPushButton("Exctract");
//    exctractButton->setFixedSize(72, buttonHeight*1.2);
    connect(exctractButton, &QPushButton::clicked, this, &PGC::exctractData);

    exitAppButton = new QPushButton("Cancel");
//    exitAppButton->setFixedSize(72, buttonHeight * 1.2);
    connect(exitAppButton, &QPushButton::clicked, this, &PGC::exitProgram);

    buttonLayout = new QHBoxLayout();
//    buttonLayout->setContentsMargins(10, 10, 10, 10);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exctractButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exitAppButton);
    buttonLayout->addStretch();

    log = new QTextBrowser(this);
    log->setFont(QFont(workingFont.family(), workingFont.pointSize() - 1));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    int l, t, r, b;
    mainLayout->getContentsMargins(&l, &t, &r, &b);
//    mainLayout->addLayout(logoLayout);
    mainLayout->addSpacing(t / 2);
    mainLayout->addLayout(startDateLayout);
    mainLayout->addSpacing(t / 2);

    mainLayout->addLayout(endDateLayout);
    mainLayout->addSpacing(t / 2);;
    mainLayout->addLayout(prodColLayout);
    mainLayout->addLayout(booksLayout);
    mainLayout->addLayout(practiceLayout);
    mainLayout->addSpacing(t / 2);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(t / 2);
    mainLayout->addWidget(log);
    mainLayout->addStretch();

    setLayout(mainLayout);
    setWindowTitle(tr("OASIS PGC Data Extractor"));

    spinner = new QtWaitingSpinner(this);
    handler = new dbHandler();

    thread = new QThread();

    handler->moveToThread(thread);
    connect(handler, SIGNAL(dbConnectError(QString)), this, SLOT(onDbconnectError(QString)));
    connect(handler, SIGNAL(dbConnectSuccessful()), this, SLOT(onDbSuccessful()));
    connect(handler, SIGNAL(extractionCompleted()), this, SLOT(onExtractionCompleted()));
    connect(handler, SIGNAL(appBookReady(map<string, string> )), this, SLOT(onQueryAppBook(map<string, string>)));
    thread->start();

//    connect(handler, SIGNAL(allCompleted()),this, SLOT(onAllCompleted()));

}

PGC::~PGC() 
{
//    thread->deleteLater();
    thread->quit();
    thread->wait();
    delete handler;

    delete pickerStart;
    delete startDateLayout;

    delete pickerEnd;
    delete endDateLayout;

    delete prodColLayout;

    delete booksSelect;
    delete booksLayout;

    delete practiceLayout;

    delete buttonLayout;
}

void PGC::initialLoad()
{
     spinner->show();
     spinner->adjustPosition();
     this->setEnabled(false);
     QMetaObject::invokeMethod(handler, "connectDatabase", Qt::QueuedConnection);
}


void PGC::onDbconnectError(QString message)
{
    QMessageBox msgBox(this);
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Warning);
    auto* connect = msgBox.addButton("Try to connect", QMessageBox::ActionRole);
    auto* exit = msgBox.addButton("Exit Program", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == connect)
    {
        initialLoad();
    }
    else if (msgBox.clickedButton() == exit)
    {
        qApp->quit();
    }
}

void PGC::onDbSuccessful()
{
    QMetaObject::invokeMethod(handler, "loadBooksAndFunctions", Qt::QueuedConnection);
}

void PGC::exctractData()
{
    /* all querying routines are call from here*/
    if (!checkBeforeExtract()) return;

    spinner->show();
    spinner->adjustPosition();
    this->setEnabled(false);

    QString start = convertDateForMimer(pickerStart->getDate());
    QString end = convertDateForMimer(pickerEnd->getDate());
    QStringList books = booksSelect->getBooks(m_books);

    int prod_columns = prodCol->currentText().toInt();
    QString practice = practiceName->text();

    QMetaObject::invokeMethod(handler, "Extract",
        Qt::QueuedConnection,
//                Qt::DirectConnection,
        Q_ARG(QString, start),
        Q_ARG(QString, end),
        Q_ARG(QStringList, books),
        Q_ARG(int, prod_columns),
        Q_ARG(QString, practice)
//        Q_ARG(QString, patched_file_path)
    );
}

bool PGC::checkBeforeExtract()
{
    bool ok;
    QStringList list1 = pickerStart->getDate().split("/");
    QDate start = QDate(list1.at(2).toInt(&ok), list1.at(1).toInt(&ok), list1.at(0).toInt(&ok));

    QStringList list2 = pickerEnd->getDate().split("/");
    QDate end = QDate(list2.at(2).toInt(&ok), list2.at(1).toInt(&ok), list2.at(0).toInt(&ok));

    if(start >= end)
    {
        QMessageBox msgBox(this);
        msgBox.setText("The Start Date cannot\nbe later or equial\nthan the End Date");
        msgBox.setIcon(QMessageBox::Warning);
        auto* ok = msgBox.addButton("Back to selection", QMessageBox::ActionRole);

        msgBox.setFont(workingFont);

        msgBox.exec();
        return false;
    }

    if (booksSelect->getText().isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setText("Please select\nat least one book");
        msgBox.setIcon(QMessageBox::Warning);
        auto* ok = msgBox.addButton("Back to selection", QMessageBox::ActionRole);

        msgBox.setFont(workingFont);

        msgBox.exec();
        return false;
    }
    if (practiceName->text().isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setText("Please enter\nthe Practice Name");
        msgBox.setIcon(QMessageBox::Warning);
        auto* ok = msgBox.addButton("Back to selection", QMessageBox::ActionRole);

        msgBox.setFont(workingFont);

        msgBox.exec();
        return false;
    }
    return true;
}

void PGC::onExtractionCompleted()
{
    spinner->hide();
    exctractButton->setEnabled(true);
    this->setEnabled(true);
}


void PGC::updateLog(QString message)
{
    //if (message != QString("\n")) 
    log->append(message);
}

void PGC::onQueryAppBook(map<string, string> books)
{
    spinner->hide();
    m_books = books;
    QStringList list;
    for (auto it = books.begin(); it != books.end(); it++)
    {
       list << QString(it->first.c_str());// = QString::fromLatin1(zero) + list.at(i);
    }
    booksSelect->getPopup().setTable(list);
    booksSelect->selectAllBooks();
    this->setEnabled(true);
}

QString PGC::convertDateForMimer(const QString date)
{
    QStringList list = date.split("/");
    auto day = list.at(0);
    auto month = list.at(1);
    auto year = list.at(2);
    return year + "-" + month + "-" + day;
}


void PGC::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);
    this->pickerStart->adjustPopupPosition();
    this->pickerEnd->adjustPopupPosition();
    this->booksSelect->adjustPopupPosition();
    this->spinner->adjustPosition();

}

void PGC::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    this->pickerStart->adjustPopupPosition();
    this->pickerEnd->adjustPopupPosition();
    this->booksSelect->adjustPopupPosition();
    this->spinner->adjustPosition();

}


void PGC::exitProgram()
{
    spinner->hide();
    QMessageBox msgBox(this);
    msgBox.setText("Confirm you want to exit program");
    msgBox.setIcon(QMessageBox::Warning);
    auto* ok = msgBox.addButton("Exit Program", QMessageBox::ActionRole);
    auto* cancel = msgBox.addButton(QMessageBox::Cancel);

    msgBox.setFont(workingFont);

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
