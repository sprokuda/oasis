#include "QtMultiSelect.h"

extern QString workingDirectory;
extern QFont workingFont;

QtMultiSelect::QtMultiSelect( QWidget* parent)
    : QWidget(parent) 
{
    this->setFont(workingFont);
    popup = new QtMultiSelectPopup(this);
    popup->installEventFilter(this);
    popup->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    edit = new QLineEdit("", this);
    edit->setReadOnly(true);
    edit->setContentsMargins(0, 0, 0, 0);

    button = new QToolButton(this);
    button->setContentsMargins(0, 0, 0, 0);
    QIcon icon;
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Normal, QIcon::On); //QString::fromUtf8("N")
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Active, QIcon::On);
    icon.addPixmap(QPixmap(workingDirectory + "\\down-100.png"), QIcon::Selected, QIcon::On);
    button->setIcon(icon);

    ctrlLayout = new QHBoxLayout(this);
    ctrlLayout->addWidget(edit);
    ctrlLayout->addWidget(button);
    ctrlLayout->setSpacing(0);
    ctrlLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(ctrlLayout);

    connect(button, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));
    connect(popup, SIGNAL(addItem(QString)), SLOT(onAddItem(QString)));
    connect(popup, SIGNAL(removeItem(QString)), SLOT(onRemoveItem(QString)));
    connect(popup, SIGNAL(clickCatched(int)), SLOT(onClickCatch(int)));
    connect(popup, SIGNAL(editingFinished()),popup, SLOT(hide()));
}


void QtMultiSelect::selectAllBooks()
{
    auto& list = popup->getBoxList();
    for (auto it = list.begin(); it != list.end(); it++)
    {
        (*it)->setCheckState(Qt::Checked);
    }
}

void QtMultiSelect::onClickCatch(int value)
{
    edit->setText(QString::number(value));
    popup->hide();
}

QString QtMultiSelect::getText()
{
    return edit->text();
}

QStringList QtMultiSelect::getBooks()
{
    auto text = edit->text();

    auto parts = text.split(";");
    parts.removeAt(parts.size() - 1);

    return parts;
}


void QtMultiSelect::adjustPopupPosition()
{
    //if (!popup->isVisible()) {
    //    return;
    //}

    int l, t, r, b;
    this->layout()->getContentsMargins(&l, &r, &t, &b);

    int lw = 1;// = this->lineWidth();

    QRect rect = edit->rect();
    QPoint bottomLeft = this->mapToGlobal(rect.topLeft());
    popup->move(bottomLeft.x() -6  + 1 + l , bottomLeft.y() + this->height()/2 + edit->height()/2- 6 +lw);

}

void QtMultiSelect::onShowPopupButtonClicked()
{
        adjustPopupPosition();
        popup->show();

}

void QtMultiSelect::onAddItem(const QString& item_text)
{
    auto text = edit->text();
    text.append(item_text);
    text.append(";");
    auto parts = text.split(";");
//    parts.removeAt(parts.lastIndexOf(";"));
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



