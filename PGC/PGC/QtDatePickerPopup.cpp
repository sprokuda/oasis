#include "QtDatePickerPopup.h"

QtDatePickerPopup::QtDatePickerPopup(QWidget* parent)
    : QWidget(parent)
{

    cndrWidget = new QCalendarWidget(this);
    hideButton = new QPushButton("Hide", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(hideButton);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(cndrWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    this->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(10.0);
    shadow_effect->setOffset(5.0);
    this->setGraphicsEffect(shadow_effect);

    QFont font = this->font();
    font.setPointSize(7);

    this->setFont(font);

    this->setWindowTitle(QObject::tr("Date Picker"));

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    connect(cndrWidget, SIGNAL(clicked(QDate)), SLOT(onCalendarDateSelected(QDate)));
    connect(hideButton, SIGNAL(clicked()), SLOT(hide()));
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

//void QtDatePickerPopup::resizeEvent(QResizeEvent* event)
//{
//    QWidget::resizeEvent(event);
//
//    QRect popup_geometry = geometry();
//    popup_geometry.moveTo(parentWidget()->mapToGlobal(parentWidget()->rect().bottomLeft()));
//    QRect screen_geometry = QApplication::desktop()->screenGeometry();
//
//    if (popup_geometry.right() > screen_geometry.right())
//        popup_geometry.moveRight(screen_geometry.right());
//    if (popup_geometry.bottom() > screen_geometry.bottom())
//        popup_geometry.moveBottom(parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y());
//
//    move(popup_geometry.topLeft());
//}
//
//
//void QtDatePickerPopup::moveEvent(QMoveEvent* event)
//{
//    QWidget::moveEvent(event);
//
//    QRect popup_geometry = geometry();
//    popup_geometry.moveTo(parentWidget()->mapToGlobal(parentWidget()->rect().bottomLeft()));
//    QRect screen_geometry = QApplication::desktop()->screenGeometry();
//
//    if (popup_geometry.right() > screen_geometry.right())
//        popup_geometry.moveRight(screen_geometry.right());
//    if (popup_geometry.bottom() > screen_geometry.bottom())
//        popup_geometry.moveBottom(parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y());
//
//    move(popup_geometry.topLeft());
//}



