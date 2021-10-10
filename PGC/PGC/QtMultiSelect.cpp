#include "QtMultiSelect.h"

extern QString workingDirectory;

QtMultiSelect::QtMultiSelect(const QFont& qfont, const int& bHeight, QWidget* parent)
    : QWidget(parent), font(qfont), buttonHeight(bHeight)
{
    popup = new QtMultiSelectPopup(font, buttonHeight, this);
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

    this->setFont(font);

    connect(button, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));
    connect(popup, SIGNAL(addItem(QString)), SLOT(onAddItem(QString)));
    connect(popup, SIGNAL(removeItem(QString)), SLOT(onRemoveItem(QString)));
}

bool QtMultiSelect::eventFilter(QObject* object, QEvent* event)
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
    if ((object == popup) && (event->type() == QEvent::WindowDeactivate)) {
        popup->close();
        emit editingFinished();
    }

    return QWidget::eventFilter(object, event);
}

QString QtMultiSelect::getText()
{
    return edit->text();
}


void QtMultiSelect::adjustPopupPosition()
{
    //if (!popup->isVisible()) {
    //    return;
    //}

    int l, t, r, b;
    this->layout()->getContentsMargins(&l, &r, &t, &b);

    int l1, t1, r1, b1;
    this->layout()->getContentsMargins(&l1, &r1, &t1, &b1);

    int lw = popup->getTable().lineWidth();

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



