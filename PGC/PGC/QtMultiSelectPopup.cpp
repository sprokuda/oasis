#include "QtMultiSelectPopup.h"
#include <QHeaderView>

QtMultiSelectPopup::QtMultiSelectPopup( QWidget* parent)
    : QWidget(parent)  
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(6.0);
    shadow_effect->setOffset(3);
    this->setGraphicsEffect(shadow_effect);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
}

QtMultiSelectPopup::~QtMultiSelectPopup()
{
    for (auto it = layout_list.begin(); it != layout_list.end(); it++)
    {
        delete *it;
    }
    for (auto it = edit_list.begin(); it != edit_list.end(); it++)
    {
        delete* it;
    }
}




void QtMultiSelectPopup::setTable(const QStringList& list)
{
    if (list.isEmpty()) return;

    for (int i = 0; i < list.size(); i++)
    {
        QLineEdit* edit = new QLineEdit(list.at(i), this);
        edit_list.push_back(edit);
        edit->setReadOnly(true);
        edit->installEventFilter(this);
        QCheckBox* box = new QCheckBox(this);
        QHBoxLayout* layout = new QHBoxLayout();
        //layout->addStrech();
        layout->addWidget(edit);
        layout->addWidget(box);
        QString word = list[i];
        connect(box, &QCheckBox::toggled, this, [=](bool if_checked) { selectItem(if_checked, word); });
        mainLayout->addLayout(layout);
        layout_list.push_back(layout);
    }
    mainLayout->installEventFilter(this);
}

void QtMultiSelectPopup::selectItem(bool state, const QString& item_text)
{
    if (state) emit addItem(item_text);
    else emit removeItem(item_text);
}

void QtMultiSelectPopup::addDummyItem(const int state)
{
    auto cb = dynamic_cast<QCheckBox*>(sender());
    auto tw = dynamic_cast<QTableWidget*>(cb->parentWidget());

    emit addItem(QString::QString("some text"));
}

void QtMultiSelectPopup::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect bakcground_rect = rect().adjusted(6, 6, -6, -6);

    QPainterPath background_path(QPoint(30, 10));
    //    background_path.lineTo(50, 10);  // TODO: draw pick according to popup position
    //    background_path.lineTo(40, 0);
//    background_path.addRoundedRect(bakcground_rect, 10, 10);
    background_path.addRect(bakcground_rect);


    painter.drawRect(bakcground_rect);
    painter.fillPath(background_path, Qt::white);
    event->accept();
}

bool QtMultiSelectPopup::eventFilter(QObject* object, QEvent* event)
{

    for (auto it = edit_list.begin(); it != edit_list.end(); it++)
    {
        if ((object == *it) && (event->type() == QEvent::MouseButtonRelease))
        {
            emit clickCatched(event->type());
        }
    }
    return QWidget::eventFilter(object, event);
}








