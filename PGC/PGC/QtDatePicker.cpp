#include "QtDatePicker.h"

extern QString workingDirectory;

QtDatePicker::QtDatePicker(QWidget* parent)
    : QWidget(parent)
{
    popup = new QtDatePickerPopup(this);
    popup->installEventFilter(this);

    edit = new QLineEdit(QDate::currentDate().toString("dd/MM/yyyy"), this);
    edit->setContentsMargins(0, 0, 0, 0);

    button = new QToolButton(this);
    button->setContentsMargins(0, 0, 0, 0);
    QIcon icon;
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Active, QIcon::On);
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Selected, QIcon::On);
    button->setIcon(icon);

    QHBoxLayout* ctrlLayout = new QHBoxLayout(this);
    ctrlLayout->addStretch();

    ctrlLayout->addWidget(edit);
//    ctrlLayout->addStretch();
    ctrlLayout->addWidget(button);

    setLayout(ctrlLayout);

    connect(button, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));
    connect(popup, SIGNAL(dateSelected(QDate)), SLOT(setDate(QDate)));
}

void QtDatePicker::setDate(QDate date)
{
    edit->setText(date.toString("dd/MM/yyyy"));
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
        popup->setDate(QString("Today: ") + QDate::currentDate().toString("dd/MM/yyyy"));
        popup->show();
}


bool QtDatePicker::eventFilter(QObject* object, QEvent* event)
{
    if ((object == popup) && (event->type() == QEvent::KeyPress))
    {
        auto* key_event = dynamic_cast<QKeyEvent*>(event);
        if (key_event->key() == Qt::Key_Escape)
        {
            popup->hide();
            emit editingFinished();
        }
    }
    if ((object == popup) && (event->type() == QKeyEvent::WindowDeactivate)) {
        popup->hide();
        emit editingFinished();
    }
    return QWidget::eventFilter(object, event);
}


