#include "help_window.h"
#include "ui_help_window.h"

help_window::help_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help_window)
{
    ui->setupUi(this);
    this->setFixedSize(670,430);
    setWindowTitle(QString("帮助文档"));
}

help_window::~help_window()
{
    delete ui;
}
