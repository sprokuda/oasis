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

    cndrWidget->setLocale(QLocale(QLocale::English, QLocale::Australia));

    cndrWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

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



//    hideButton = new QPushButton("Hide", this);

//    QHBoxLayout* buttonLayout = new QHBoxLayout;
//    buttonLayout->addStretch();
//    buttonLayout->addWidget(hideButton);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(cndrWidget);
//    mainLayout->addLayout(buttonLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    this->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(10.0);
    shadow_effect->setOffset(5.0);
    this->setGraphicsEffect(shadow_effect);

    this->setWindowTitle(QObject::tr("Date Picker"));

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    connect(cndrWidget, SIGNAL(clicked(QDate)), SLOT(onCalendarDateSelected(QDate)));
//    connect(hideButton, SIGNAL(clicked()), SLOT(hide()));
}

void QtDatePickerPopup::onCalendarDateSelected(const QDate& date)
{
    emit dateSelected(date);
}

void QtDatePickerPopup::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect bakcground_rect = rect().adjusted(10, 10, -10, -10);

    QPainterPath background_path(QPoint(30, 10));
    ////    background_path.lineTo(50, 10);  // TODO: draw pick according to popup position
    ////    background_path.lineTo(40, 0);
//    background_path.addRoundedRect(bakcground_rect, 10, 10);
    background_path.addRect(bakcground_rect);

    painter.fillPath(background_path, Qt::gray);

    event->accept();
}





