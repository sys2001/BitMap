#include "showbitmap.h"
#include "ui_showbitmap.h"

showBitmap::showBitmap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::showBitmap)
{
    ui->setupUi(this);
}

showBitmap::~showBitmap()
{
    delete ui;
}
