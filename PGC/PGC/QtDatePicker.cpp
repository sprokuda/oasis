#include "QtDatePicker.h"


QtDatePicker::QtDatePicker(QWidget* parent)
    : QWidget(parent)
{
    popup = new QtDatePickerPopup(this);
    popup->installEventFilter(this);

    edit = new QLineEdit(QDate::currentDate().toString(), this);
    showPP = new QPushButton("PickDate", this);

    QHBoxLayout* ctrlLayout = new QHBoxLayout(this);
//    ctrlLayout->addStretch();
    ctrlLayout->addWidget(edit);
    ctrlLayout->addStretch();
    ctrlLayout->addWidget(showPP);

    setLayout(ctrlLayout);

    connect(showPP, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));
    connect(popup, SIGNAL(dateSelected(QDate)), SLOT(setDate(QDate)));
}

void QtDatePicker::setDate(QDate date)
{
    edit->setText(date.toString());
    //QString::number(QDate::currentDate().month()) + "/" + QString::number(QDate::currentDate().year())
}

void QtDatePicker::adjustPopupPosition()
{
    QRect popup_geometry = popup->geometry();
    popup_geometry.moveTo(this->mapToGlobal(edit->rect().bottomLeft()));
    popup->move(popup_geometry.topLeft().x() - 1, popup_geometry.topLeft().y() - 1);
}

void QtDatePicker::onShowPopupButtonClicked()
{
        adjustPopupPosition();
        popup->show();
}


bool QtDatePicker::eventFilter(QObject* object, QEvent* event)
{
    if ((object == popup) && (event->type() == QEvent::WindowDeactivate)) {
        popup->hide();
        emit editingFinished();
    }

    return QWidget::eventFilter(object, event);
}


