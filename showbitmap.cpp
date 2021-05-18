#include "showbitmap.h"
#include "ui_showbitmap.h"
int sta_Num=8;
int delay=1;
int opt=NOINPUT;
showBitmap::showBitmap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::showBitmap)
{
    ui->setupUi(this);
    sta_Num=8;
    delay=3;
    Init();
}

showBitmap::~showBitmap()
{
    delete ui;
}

void showBitmap::Init()
{
    
}

void showBitmap::mousePressEvent(QMouseEvent *event)
{
    QPoint pt;          //鼠标按下时对应的格子
    pt.setX((event->pos().x()-START_X)/BLOCK_WIDTH);    //映射到数组下标
    pt.setY(event->pos().y());                          //判断是否选择某个站点
    if(pt.y()>=START_Y&&pt.y()<=START_Y+BLOCK_HEIGHT){  //在站点Y轴范围内
        if(pt.x()>=0&&pt.x()<Sta_Num){
            stations[pt.x()]->wait=true;                //该站点有数据需要发送
        }
        else{
            return;                                     //不在站点X轴范围内
        }
    }
    else{
        return ;                                        //未点击站点，忽视此次点击事件
    }
}


void showBitmap::on_station_triggered()
{
    opt=STANUM;
    StationSettingWindows = new Dialog(this);
    StationSettingWindows->show();
    opt=NOINPUT;
}
