#include "QtDatePicker.h"

extern QString workingDirectory;
extern QFont workingFont;

QtDatePicker::QtDatePicker(QWidget* parent)
    : QWidget(parent)
{
    this->setFont(workingFont);
    popup = new QtDatePickerPopup(this);
    popup->installEventFilter(this);

    edit = new QLineEdit(QDate::currentDate().toString("dd/MM/yyyy"), this);
    edit->setContentsMargins(0, 0, 0, 0);
    edit->setReadOnly(true);
    button = new QToolButton(this);
    button->setContentsMargins(0, 0, 0, 0);
    QIcon icon;
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Active, QIcon::On);
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Selected, QIcon::On);
    button->setIcon(icon);

    QHBoxLayout* ctrlLayout = new QHBoxLayout(this);
    ctrlLayout->setContentsMargins(0, 0, 0, 0);
    ctrlLayout->setSpacing(0);
    ctrlLayout->addStretch();
    ctrlLayout->addWidget(edit);
//    ctrlLayout->addStretch();
    ctrlLayout->addWidget(button);

    setLayout(ctrlLayout);

    connect(button, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));
    connect(popup, SIGNAL(dateSelected(QDate)), SLOT(setDate(QDate)));
}

QString QtDatePicker::getDate()
{
    return edit->text();
}

void QtDatePicker::setDate(QDate date)
{
    edit->setText(date.toString("dd/MM/yyyy"));
 //   popup->close();

    int begin = 2;
    int end = 5;
 //   edit->setSelection(3, 4);

    //QString::number(QDate::currentDate().month()) + "/" + QString::number(QDate::currentDate().year())
}

void QtDatePicker::adjustPopupPosition()
{
    int l, r, t, b;
    this->layout()->getContentsMargins(&l, &t, &r, &b);

    QRect rect = edit->rect();
    QPoint bottomLeft = this->mapToGlobal(rect.topLeft());
    popup->move(bottomLeft.x() - 6 + 1 + l, bottomLeft.y() + this->height() / 2 + edit->height() / 2 - 6 );
}

void QtDatePicker::onShowPopupButtonClicked()
{
        adjustPopupPosition();
        popup->setDate(QDate::currentDate().toString("dd/MM/yyyy"));
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
    //if ((object == popup) && (event->type() == QEvent::MouseButtonDblClick))
    //{
    ////    auto* key_event = dynamic_cast<QKeyEvent*>(event);
    ////   if (key_event->key() == Qt::Key_Escape)
    ////    {
    //        popup->hide();
    //        emit editingFinished();
    ////    }
    //}
    if ((object == popup) && (event->type() == QKeyEvent::WindowDeactivate)) {
        popup->hide();
        emit editingFinished();
    }
    if ((object == popup) && (event->type() == QEvent::MouseButtonDblClick)) {
        popup->hide();
        emit editingFinished();
    }
    return QWidget::eventFilter(object, event);
}


