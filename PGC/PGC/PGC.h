#pragma once

#include <QtWidgets/QWidget>
#include "ui_PGC.h"

class PGC : public QWidget
{
    Q_OBJECT

public:
    PGC(QWidget *parent = Q_NULLPTR);

private:
    Ui::PGCClass ui;
};
