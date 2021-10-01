#include "QtDatePicker.h"


QtDatePicker::QtDatePicker(QWidget* parent)
    : QWidget(parent)
{
    popup = new QtDatePickerPopup(this);

    edit = new QLineEdit("xxxx", this);
    showPP = new QPushButton("PickDate", this);

    QHBoxLayout* ctrlLayout = new QHBoxLayout(this);
//    ctrlLayout->addStretch();
    ctrlLayout->addWidget(edit);
    ctrlLayout->addStretch();
    ctrlLayout->addWidget(showPP);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(ctrlLayout);
    setLayout(ctrlLayout);

    connect(showPP, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));
    connect(popup, SIGNAL(dateSelected(QDate)), SLOT(setDate(QDate)));
}

void QtDatePicker::adjustPopupPosition()
{
//    const QPoint global = parentWidget()->mapToGlobal(edit->rect().bottomLeft());
//    popup->move(global.x() , global.y() );//edit->height()//- edit->width()/2

    QRect popup_geometry = popup->geometry();
    popup_geometry.moveTo(this->mapToGlobal(edit->rect().bottomLeft()));
    //QRect screen_geometry = QApplication::desktop()->screenGeometry(this);

    //if (popup_geometry.right() > screen_geometry.right())
    //    popup_geometry.moveRight(screen_geometry.right());
    //if (popup_geometry.bottom() > screen_geometry.bottom())
    //    popup_geometry.moveBottom(this->mapToGlobal(this->rect().topLeft()).y());

    popup->move(popup_geometry.topLeft());
}

void QtDatePicker::onShowPopupButtonClicked()
{
//    if (!popup->isVisible()) {
        adjustPopupPosition();
        popup->show();
        popup->raise();
        popup->activateWindow();
//    }
}

