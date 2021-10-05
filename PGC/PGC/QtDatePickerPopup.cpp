#include "QtDatePickerPopup.h"

extern QString workingDirectory;

QtDatePickerPopup::QtDatePickerPopup(QWidget* parent)
    : QWidget(parent)
{
    QFont font = this->font();
    font.setFamily("Calibri");
    font.setPointSize(10);
    this->setFont(font);

    cndrWidget = new QCalendarWidget(this);
    cndrWidget->setContentsMargins(0, 0, 0, 0);
    cndrWidget->setLocale(QLocale(QLocale::English, QLocale::Australia));

    cndrWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
//    cndrWidget->setDateEditEnabled(false);
    cndrWidget->setSelectedDate(QDate::currentDate());

    QWidget* calendarNavBar = cndrWidget->findChild<QWidget*>("qt_calendar_navigationbar");
    if (calendarNavBar) 
    {
        QPalette pal = calendarNavBar->palette();
        pal.setColor(calendarNavBar->backgroundRole(), QColor(255, 255, 255));
        pal.setColor(calendarNavBar->foregroundRole(), QColor(0, 0, 0));
        calendarNavBar->setPalette(pal);
    }

    QToolButton* btn = cndrWidget->findChild<QToolButton*>("qt_calendar_prevmonth");
    if (btn)
    {
        QIcon icon;
        icon.addPixmap(QPixmap(workingDirectory + "\\left-100.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
        icon.addPixmap(QPixmap(workingDirectory + "\\left-100.png"), QIcon::Active, QIcon::On);
        icon.addPixmap(QPixmap(workingDirectory + "\\left-100.png"), QIcon::Selected, QIcon::On);
        btn->setIcon(icon);

        btn = cndrWidget->findChild<QToolButton*>("qt_calendar_nextmonth");
        icon.addPixmap(QPixmap(workingDirectory + "\\right-100.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
        icon.addPixmap(QPixmap(workingDirectory + "\\right-100.png"), QIcon::Active, QIcon::On);
        icon.addPixmap(QPixmap(workingDirectory + "\\right-100.png"), QIcon::Selected, QIcon::On);
        btn->setIcon(icon);
    }

    QToolButton* call_btn = cndrWidget->findChild<QToolButton*>("qt_calendar_monthbutton");
    if (call_btn)
    {
        QFont navigatorBarFont("Calibri", 10, QFont::Medium);
        call_btn->setFont(navigatorBarFont);
    }

    call_btn = cndrWidget->findChild<QToolButton*>("qt_calendar_yearbutton");
    if (call_btn)
    {
        QFont navigatorBarFont("Calibri", 10, QFont::Medium);
        call_btn->setFont(navigatorBarFont);
    }

    QHBoxLayout* cndrLayout = new QHBoxLayout;
    cndrLayout->addStretch();
    cndrLayout->addWidget(cndrWidget);
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
    shadow_effect->setBlurRadius(10.0);
    shadow_effect->setOffset(5.0);
    this->setGraphicsEffect(shadow_effect);

    this->setWindowTitle(QObject::tr("Date Picker"));

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    connect(cndrWidget, SIGNAL(clicked(QDate)), SLOT(onCalendarDateSelected(QDate)));
    connect(todayButton, SIGNAL(clicked()), this,SLOT(onTodayButton()));
}

void QtDatePickerPopup::onCalendarDateSelected(const QDate& date)
{
    emit dateSelected(date);
}

void QtDatePickerPopup::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::darkGray, 1));
    QRect bakcground_rect = rect().adjusted(11, 11, -11, -11);
 
    QPainterPath background_path(QPoint(30, 10));
    background_path.addRect(bakcground_rect);

    painter.drawRect(bakcground_rect);
    painter.fillPath(background_path, Qt::white);
    event->accept();
}

void QtDatePickerPopup::setDate(const QString& text) 
{
    label->setText(text);
//    cndrWidget->setSelectedDate(QDate::currentDate());
}

void QtDatePickerPopup::onTodayButton()
{
    label->setText(QDate::currentDate().toString("dd/MM/yyyy"));
    cndrWidget->setSelectedDate(QDate::currentDate());
    emit dateSelected(QDate::currentDate());
}



