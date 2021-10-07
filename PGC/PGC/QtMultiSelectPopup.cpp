#include "QtMultiSelectPopup.h"
#include <QHeaderView>

QtMultiSelectPopup::QtMultiSelectPopup(const QFont& qfont, const int& bHeight, QWidget* parent)
    : QWidget(parent), font(qfont), buttonHeight(bHeight)
{
    QFont headerFont(font.family(), 9);

    table = new QTableWidget(3,2,this);
    table->setHorizontalHeaderLabels({ "Book","Select" });
    table->horizontalHeader()->setFont(headerFont);
    table->verticalHeader()->setFont(headerFont);

    edit_width = 80;
    check_width = 44;
    header_width = 20;

    table->setColumnWidth(0, edit_width);
    table->setColumnWidth(1, check_width);
    table->verticalHeader()->setFixedWidth(header_width);
//    table->setFrameShape(QFrame::NoFrame);
    table->setShowGrid(true);
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(table);
//    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    int l1, r1, t1, b1;
    table->getContentsMargins(&l1, &t1, &r1, &b1);
    int l, r, t, b;
    mainLayout->getContentsMargins(&l, &t, &r, &b);
    mainLayout->setSpacing(0);
    total_width = edit_width + check_width +l+r+ 6;
    int total_height = table->rowHeight(0)*3 + t+ b + 6;
    table->setContentsMargins(0, 0, 0, 0);
    this->setFixedSize(total_width, total_height);


    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(6.0);
    shadow_effect->setOffset(3);
    this->setGraphicsEffect(shadow_effect);

    this->setFont(font);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
//    this->resize(total_width, total_height);

//    connect(hideButton, SIGNAL(clicked()), SLOT(hide()));
}

int QtMultiSelectPopup::width()
{
    return total_width;
}

void QtMultiSelectPopup::setTable(const QStringList& lst)
{
    if (lst.isEmpty()) return;
//    int columnCheckBoxWidth;


    for (size_t i = 0; i < lst.size(); i++)
    {
        QLineEdit* edit = new QLineEdit(lst[i]);
        edit->setEnabled(false);
        edit->setFont(font);
        edit->setFixedWidth(edit_width);

        table->setCellWidget(i, 0, edit);

        QCheckBox* checkBox = new QCheckBox();
        checkBox->setStyleSheet("text-align: center; margin-left:15%; margin-right:15%;");
        QString word = lst[i];
        connect(checkBox, &QCheckBox::toggled, this, [=](bool if_checked) { selectItem(if_checked, word); });

        table->setCellWidget(i, 1, checkBox);
    }
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








