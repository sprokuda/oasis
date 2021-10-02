#include "QtMultiSelect.h"

QtMultiSelect::QtMultiSelect(const QFont& qfont, const int& bHeight, QWidget* parent)
    : QWidget(parent), font(qfont), buttonHeight(bHeight)
{
    
    popup = new QtMultiSelectPopup(font, buttonHeight, this);

//    popup->installEventFilter(this);
//    popup->adjustSize();

    edit = new QLineEdit("", this);
    edit->setFixedWidth(popup->width()+2);
//    edit->setFixedHeight(buttonHeight);
    showPP = new QPushButton("Select books", this);
//    showPP->setFixedHeight(buttonHeight);

    ctrlLayout = new QHBoxLayout(this);
    ctrlLayout->addWidget(edit);
    ctrlLayout->addWidget(showPP);

    setLayout(ctrlLayout);

    this->setFont(font);

    connect(showPP, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));
    connect(popup, SIGNAL(addItem(QString)), SLOT(onAddItem(QString)));
    connect(popup, SIGNAL(removeItem(QString)), SLOT(onRemoveItem(QString)));
}

void QtMultiSelect::adjustPopupPosition()
{
    QRect popup_geometry = popup->geometry();
    popup_geometry.moveTo(this->mapToGlobal(edit->rect().bottomLeft()));
    popup->move(popup_geometry.topLeft().x()-1, popup_geometry.topLeft().y()-1);
}

void QtMultiSelect::onShowPopupButtonClicked()
{
        adjustPopupPosition();
        popup->show();
//        popup->raise();
//        popup->activateWindow();

}

void QtMultiSelect::onAddItem(const QString& item_text)
{
    auto text = edit->text();
    text.append(item_text);
    text.append(";");
    auto parts = text.split(";");
    parts.removeAt(parts.lastIndexOf(";"));
    parts.removeAt(parts.size() - 1);
    parts.sort();
    auto out_text = parts.join(";");
    if (!out_text.isEmpty()) out_text.append(";");
    edit->setText(out_text);
}

void QtMultiSelect::onRemoveItem(const QString& item_text)
{
    auto text = edit->text();
    auto parts = text.split(";");
    parts.removeAt(parts.size()-1);
    parts.removeAt(parts.indexOf(item_text));
    parts.removeAt(parts.lastIndexOf(";"));
    parts.sort();
    auto out_text = parts.join(";");
    if (!out_text.isEmpty()) out_text.append(";");
    edit->setText(out_text);
}



