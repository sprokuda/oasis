#include <QIcon>


#include "PGC.h"

PGC::PGC(QWidget *parent)
    : QWidget(parent)
{
    QIcon icon;

    QIcon::Mode mode = QIcon::Normal;
    QIcon::State state = QIcon::On;

    const QString fileName = "./centaur-logo.png";
    QImage image(fileName);
    if (!image.isNull())
        icon.addPixmap(QPixmap::fromImage(image), mode, state);
}
