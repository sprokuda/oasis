#include "QtWaitingSpinner.h"
#include <QMovie>
#include <QLayout>

extern QString workingDirectory;

QtWaitingSpinner::QtWaitingSpinner(QWidget* parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel(this);

    QMovie* movie = new QMovie(":/PGC/resources/ajax-loader.gif");
    label->setMovie(movie);
    movie->start();


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);
}



void QtWaitingSpinner::adjustPosition()
{
    const QPoint global = parentWidget()->mapToGlobal(parentWidget()->rect().center());
    this->move(global.x() - width()/2 , global.y() - height()/2);//edit->height()//- edit->width()/2
}

