#include "showbitmap.h"
#include "ui_showbitmap.h"
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QStack>
#include <QQueue>
#include <windows.h>
#include "help_window.h"
int status=BEGIN;

showBitmap::showBitmap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::showBitmap)
{
    this->setFixedSize(670,430);
    ui->setupUi(this);
    //用数组存8个按钮，方便操作
    mybtn.push_back(ui->station1);
    mybtn.push_back(ui->station2);
    mybtn.push_back(ui->station3);
    mybtn.push_back(ui->station4);
    mybtn.push_back(ui->station5);
    mybtn.push_back(ui->station6);
    mybtn.push_back(ui->station7);
    mybtn.push_back(ui->station8);
    len_label.push_back(ui->len_1);
    len_label.push_back(ui->len_2);
    len_label.push_back(ui->len_3);
    len_label.push_back(ui->len_4);
    len_label.push_back(ui->len_5);
    len_label.push_back(ui->len_6);
    len_label.push_back(ui->len_7);
    len_label.push_back(ui->len_8);
    ui->sendstation->setFont(QFont("宋体",SEND_LABEL_SIZE));//
    ui->Tips->setFont(QFont("宋体",SEND_LABEL_SIZE));//tips字体
    stations.resize(BLOCK_NUM);     //改变数组大小，stations存站点是否有数据需要发送
    data_len.resize(BLOCK_NUM);
    mode=NORMAL;                    //演示模式
    cur_pos=0;                      //当前时间正在检测的站点下标
    istimestart=false;              //是否开始计时
    time_flag=0;                    //计数器初始化
    timer = new QTimer;             //定义一个定时器
    TimeRecord = new QTime(0,0,0);  //初始化时间
    ui->CLOCK->setDigitCount(8);    //定时器UI设置
    ui->CLOCK->setSegmentStyle(QLCDNumber::Flat);
    ui->CLOCK->display(TimeRecord->toString("hh:mm:ss"));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));    //连接槽函数
    oneturn=false;                  //没有经过一轮检测
    //这里可以添加图片
    //QPixmap pixData(":/Image/back_btn.jpeg");
    //DataReady = new QIcon(pixData);
    Init(mode);                     //布局初始化，根据不同的模式初始化

    connect(ui->normal,SIGNAL(triggered()),this,SLOT(on_normal_triggered()));
    connect(ui->low,SIGNAL(triggered()),this,SLOT(on_low_triggered()));
    connect(ui->high,SIGNAL(triggered()),this,SLOT(on_high_triggered()));

    ui->lowest->setText("500");
    ui->highest->setText("500");

    ui->label_14->setText("");
    ui->label_15->setText("");
    ui->denominator->setText("");
}

showBitmap::~showBitmap()
{
    delete ui;
}

void showBitmap::Init(Mode mode)
{
    stations_clear();
    cur_pos=0;              //从第一个站点开始检测
    mybtn[cur_pos]->setStyleSheet("background-color:red");
    //设置按钮的UI
    for(int i=0;i<BLOCK_NUM;i++){
        mybtn[i]->setFont(QFont("宋体",STA_BTN_SIZE));
    }
    switch (mode){
    case LOW:
        ui->title->setText("低负载");
        break;
    case HIGH:
        ui->title->setText("高负载");

        break;
    case NORMAL:
        ui->title->setText("自定义负载");
        break;
    }
    this->mode=mode;
    ui->begin->setText("开始演示");
}

//用于清空所有的站点信息，用于初始化
void showBitmap::stations_clear()
{
    cur_pos=0;
    send_num=0;
    for(int i=0;i<BLOCK_NUM;i++){
        stations[i]=false;                  //站点数据清空
        //恢复默认界面
        mybtn[i]->setText("0");
        mybtn[i]->setStyleSheet("background-color:lightGray");
        mybtn[i]->setFont(QFont("宋体",STA_BTN_SIZE));
    }
    mybtn[cur_pos]->setStyleSheet("background-color:red");

    for(int i=0;i<BLOCK_NUM;i++){
        data_len[i]=0;
        len_label[i]->setText("");
    }
}

//点击help菜单给出对应提示
void showBitmap::on_help_triggered()
{
    help_window *subWindow = new help_window();
    subWindow->show();
}

//点击开始按钮进行演示
void showBitmap::on_begin_clicked()
{
    //istimestart判断当前计时器是否已经启动，如果启动则暂停当前计时
    if(!istimestart){
        timer->start(1000);
        ui->begin->setText("暂停演示");
    }
    else{
        timer->stop();
        ui->begin->setText("开始演示");
    }
    istimestart=!istimestart;
}
//更新定时器界面，演示过程为每1秒检测一个站点，每个站点发送数据需要2秒。
void showBitmap::updateTime()
{
    int highboard=ui->highest->text().toUInt();
    int lowboard=ui->lowest->text().toUInt();
    if(lowboard>highboard)
        ui->lowest->setText(QString::number(highboard));
    static QQueue<int> ready;
    *TimeRecord = TimeRecord->addSecs(1);                   //每次加1秒
    ui->CLOCK->display(TimeRecord->toString("hh:mm:ss"));

    if(mode==HIGH){
        on_station1_clicked();
        on_station2_clicked();
        on_station3_clicked();
        on_station4_clicked();
        on_station5_clicked();
        on_station6_clicked();
        on_station7_clicked();
        on_station8_clicked();
    }
    if(mode==LOW){
        on_station1_clicked();
    }

    //检测过程
    if(cur_pos<BLOCK_NUM){                                  //未到最后一个站点，一直增加
        ui->Tips->clear();
        if(stations[cur_pos]==true){
            res+=QString::number(cur_pos+1)+" ";
            ready.push_back(cur_pos+1);
            send_num++;
            stations[cur_pos]=false;    //计算完设为false
            mybtn[cur_pos]->setText("0");

            data_len[cur_pos]=qrand()%(highboard-lowboard+1)+lowboard;
            len_label[cur_pos]->setText(QString::number(data_len[cur_pos]));
            len_label[cur_pos]->setFont(QFont("宋体",12));
        }
        mybtn[cur_pos]->setStyleSheet("background-color:lightGray");
        cur_pos++;
        if(cur_pos!=BLOCK_NUM){
            mybtn[cur_pos]->setStyleSheet("background-color:red");
        }

    }
    if(send_num==0){
        ui->Tips->clear();
        for(int i=0;i<BLOCK_NUM;i++){
            data_len[i]=0;
            len_label[i]->setText("");
        }
    }
    //数据发送过程
    if(oneturn&&send_num>0){
        if(time_flag%2){
            mybtn[ready.front()-1]->setStyleSheet("background-color:red");
        }
        else{
            mybtn[ready.front()-1]->setStyleSheet("background-color:lightGray");
        }
        int send_time=DATA_DELAY*data_len[ready.front()-1];
        if(time_flag==send_time/(DATA_DELAY*50)){
            send_num--;
            mybtn[ready.front()-1]->setStyleSheet("background-color:lightGray");
            ready.pop_front();
            time_flag=0;
            //send_time=0;
        }
        time_flag++;
        if(!ready.isEmpty()){
            QString cur_tip="正在发送站点";
            ui->Tips->setText(cur_tip+QString::number(ready.front())+"的数据,预计时间"
                              +QString::number(send_time)+"秒");
        }
        if(send_num==0){            //发送完成，开始新的一轮
            ui->Tips->setText("发送完成");
            cur_pos=0;
            mybtn[cur_pos]->setStyleSheet("background-color:red");
            oneturn=false;
            ui->rate->setText("");
            ui->sendstation->clear();
        }
    }
    //一轮结束时的判断
    if(cur_pos==BLOCK_NUM&&oneturn==false){                 //刚好是一轮结束
        int data_len_sum=0;
        for(int i=0;i<BLOCK_NUM;i++){
            data_len_sum+=data_len[i];
        }
        ui->total_len->setText(QString::number(data_len_sum));
        ui->total_len->setFont(QFont("宋体",14));
        if(send_num==0){
            ui->rate->setText("0%");
            ui->rate->setFont(QFont("宋体",14));
        }
        else{
            float rate=0;
            if(this->mode==HIGH || send_num==BLOCK_NUM)
            {
                ui->label_14->setText("d");
                ui->label_15->setText("------ =");
                ui->denominator->setText("d+1");
                rate=float(data_len_sum)/float(1+data_len_sum);
            }
            else
            {
                ui->label_14->setText("d");
                ui->label_15->setText("------ =");
                ui->denominator->setText("N+d");
                rate=float(data_len_sum)/float(send_num*BLOCK_NUM+data_len_sum);
            }
            rate*=100;
            ui->rate->setText(QString::number(rate,'f',2)+"%");
            ui->rate->setFont(QFont("宋体",14));
        }
        oneturn=true;                                       //标志位,说明竞争期结束
        if(send_num==0){
            ui->Tips->setText("本次无站点需要发送，再次轮询");
            cur_pos=0;
            oneturn=false;
            mybtn[cur_pos]->setStyleSheet("background-color:red");
        }
        else{
            QString tip="本次有"+QString::number(send_num)+"个站点需要发送，准备发送数据";
            ui->sendstation->setText(res);
            ui->Tips->setText(tip);
            res.clear();
        }

    }
}

void showBitmap::on_end_clicked()
{
    timer->stop();          //计时停止
    istimestart=false;      //设置为非计时状态
    oneturn=false;          //设置为初始状态
    TimeRecord->setHMS(0,0,0);      //时间复位
    ui->CLOCK->display(TimeRecord->toString("hh:mm:ss"));
    stations_clear();       //清空站点信息
    ui->Tips->clear();
    ui->sendstation->clear();
    ui->rate->setText("");
    ui->total_len->setText("");
    ui->label_14->setText("");
    ui->label_15->setText("");
    ui->denominator->setText("");
}

void showBitmap::on_station1_clicked()
{
    stations[0]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station1->setText("1");
}


void showBitmap::on_station2_clicked()
{
    stations[1]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station2->setText("1");
}


void showBitmap::on_station3_clicked()
{
    stations[2]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station3->setText("1");
}

void showBitmap::on_station4_clicked()
{
    stations[3]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station4->setText("1");
}

void showBitmap::on_station5_clicked()
{
    stations[4]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station5->setText("1");
}

void showBitmap::on_station6_clicked()
{
    stations[5]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station6->setText("1");
}

void showBitmap::on_station7_clicked()
{

    stations[6]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station7->setText("1");
}

void showBitmap::on_station8_clicked()
{
    stations[7]=true;
    //ui->station1->setIcon(*DataReady);
    ui->station8->setText("1");
}

void showBitmap::on_normal_triggered()
{
    Init(NORMAL);
    on_end_clicked();
}

void showBitmap::on_low_triggered()
{
    Init(LOW);
    on_end_clicked();
}

void showBitmap::on_high_triggered()
{
    Init(HIGH);
    on_end_clicked();
}
