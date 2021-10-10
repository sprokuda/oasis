#include "QtDatePickerPopup.h"

extern QString workingDirectory;

QtDatePickerPopup::QtDatePickerPopup(QWidget* parent)
    : QWidget(parent)
{
    QFont font = this->font();
    font.setFamily("Calibri");
    font.setPointSize(10);
    this->setFont(font);

    calendar = new QCalendarWidget(this);
    calendar->setMaximumDate(QDate::currentDate());
    calendar->setContentsMargins(0, 0, 0, 0);
    calendar->setLocale(QLocale(QLocale::English, QLocale::Australia));

    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
//    cndrWidget->setDateEditEnabled(false);
    calendar->setSelectedDate(QDate::currentDate());

    QWidget* calendarNavBar = calendar->findChild<QWidget*>("qt_calendar_navigationbar");
    if (calendarNavBar) 
    {
        QPalette pal = calendarNavBar->palette();
        pal.setColor(calendarNavBar->backgroundRole(), QColor(255, 255, 255));
        pal.setColor(calendarNavBar->foregroundRole(), QColor(0, 0, 0));
        calendarNavBar->setPalette(pal);
    }

    QToolButton* btn = calendar->findChild<QToolButton*>("qt_calendar_prevmonth");
    if (btn)
    {
        QIcon icon;
        icon.addPixmap(QPixmap(workingDirectory + "\\left-100.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
        icon.addPixmap(QPixmap(workingDirectory + "\\left-100.png"), QIcon::Active, QIcon::On);
        icon.addPixmap(QPixmap(workingDirectory + "\\left-100.png"), QIcon::Selected, QIcon::On);
        btn->setIcon(icon);

        btn = calendar->findChild<QToolButton*>("qt_calendar_nextmonth");
        icon.addPixmap(QPixmap(workingDirectory + "\\right-100.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
        icon.addPixmap(QPixmap(workingDirectory + "\\right-100.png"), QIcon::Active, QIcon::On);
        icon.addPixmap(QPixmap(workingDirectory + "\\right-100.png"), QIcon::Selected, QIcon::On);
        btn->setIcon(icon);
    }

    QToolButton* call_btn = calendar->findChild<QToolButton*>("qt_calendar_monthbutton");
    if (call_btn)
    {
        QFont navigatorBarFont("Calibri", 10, QFont::Medium);
        call_btn->setFont(navigatorBarFont);
    }

    call_btn = calendar->findChild<QToolButton*>("qt_calendar_yearbutton");
    if (call_btn)
    {
        QFont navigatorBarFont("Calibri", 10, QFont::Medium);
        call_btn->setFont(navigatorBarFont);
    }

    QHBoxLayout* cndrLayout = new QHBoxLayout;
    cndrLayout->addStretch();
    cndrLayout->addWidget(calendar);
    cndrLayout->addStretch();

    label = new QLabel(this);
    label->setText(QString("Today: ") + QDate::currentDate().toString("dd/MM/yyyy"));

    todayButton = new QToolButton(this);
    QIcon icon;
    icon.addPixmap(QPixmap(workingDirectory + "\\today-52.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
    icon.addPixmap(QPixmap(workingDirectory + "\\today-52.png"), QIcon::Active, QIcon::On);
    icon.addPixmap(QPixmap(workingDirectory + "\\today-52.png"), QIcon::Selected, QIcon::On);
    todayButton->setIcon(icon);

    QHBoxLayout* labelLayout = new QHBoxLayout;
    labelLayout->addStretch();
    labelLayout->addWidget(todayButton);
    labelLayout->addWidget(label);
    labelLayout->addStretch();


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
//    mainLayout->addWidget(cndrWidget);
    mainLayout->addLayout(cndrLayout);
    mainLayout->addLayout(labelLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(6.0);
    shadow_effect->setOffset(3.0);
    this->setGraphicsEffect(shadow_effect);

    this->setWindowTitle(QObject::tr("Date Picker"));

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    connect(calendar, SIGNAL(clicked(QDate)), SLOT(onCalendarDateSelected(QDate)));
    connect(todayButton, SIGNAL(clicked()), this,SLOT(onTodayButton()));

    delay = new callDelay();
    thread = new QThread();
    delay->moveToThread(thread);

    connect(delay, SIGNAL(delayFinished()), this, SLOT(onDelayFinished()));
    thread->start();
}

QtDatePickerPopup::~QtDatePickerPopup()
{
    thread->quit();
    thread->wait();
    delete delay;
}



void QtDatePickerPopup::onCalendarDateSelected(const QDate& date)
{
    QMetaObject::invokeMethod(delay, "doDelay", Qt::QueuedConnection);
    emit dateSelected(date);
}

void QtDatePickerPopup::onDelayFinished()
{
    hide();
}

void QtDatePickerPopup::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::darkGray, 1));
    QRect bakcground_rect = rect().adjusted(6, 6, -6, -6);
 
    QPainterPath background_path(QPoint(30, 10));
    background_path.addRect(bakcground_rect);

    painter.drawRect(bakcground_rect);
    painter.fillPath(background_path, Qt::white);
    event->accept();
}

void QtDatePickerPopup::setDate(const QString& text) 
{
    label->setText("Today: " + text);
//    cndrWidget->setSelectedDate(QDate::currentDate());
}

void QtDatePickerPopup::onTodayButton()
{
    label->setText("Today: " + QDate::currentDate().toString("dd/MM/yyyy"));
    calendar->setSelectedDate(QDate::currentDate());
    QMetaObject::invokeMethod(delay, "doDelay", Qt::QueuedConnection);
    emit dateSelected(QDate::currentDate());
}



