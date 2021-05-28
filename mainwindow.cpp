#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(670,430);
    setWindowTitle(QString("欢迎界面"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_entry_clicked()
{
    this->close();
    showBitmap *subWindow = new showBitmap();
    subWindow->setWindowTitle(QString("模拟控制台"));
    subWindow->show();
}
