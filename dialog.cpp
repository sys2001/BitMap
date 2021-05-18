#include "dialog.h"
#include "ui_dialog.h"
extern int delay;       //延时，传给showbitmap
extern int sta_Num;     //站点数量
extern int opt;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->inputEdit->setPlaceholderText("请输入");     //设置默认占位信息
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_ack_clicked()
{
    //暂时没写错误判断
    QString str;
    str=ui->inputEdit->text();
    switch(opt){
        case STANUM:
            sta_Num=str.toInt();
            break;
        case DELAY:
            delay=str.toInt();
            break;
        default:
            break;
    }
    close();
}

void Dialog::on_back_clicked()
{
    close();
}
