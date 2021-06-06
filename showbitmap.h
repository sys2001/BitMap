#ifndef SHOWBITMAP_H
#define SHOWBITMAP_H

#include <QMainWindow>
#include <QVector>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QPalette>
#include <QtGlobal>
#include "utils.h"
#include <QLabel>



namespace Ui {
class showBitmap;
}


class showBitmap : public QMainWindow
{
    Q_OBJECT

public:
    explicit showBitmap(QWidget *parent = 0);
    ~showBitmap();
    
    void Init(Mode mode=NORMAL);            //初始化，显示


private slots:
    void updateTime();

    void on_help_triggered();

    void on_begin_clicked();

    void on_end_clicked();

    void on_station1_clicked();

    void on_station2_clicked();

    void on_station3_clicked();

    void on_station4_clicked();

    void on_station5_clicked();

    void on_station6_clicked();

    void on_station7_clicked();

    void on_station8_clicked();

    void on_normal_triggered();

    void on_low_triggered();

    void on_high_triggered();
private:
    Ui::showBitmap *ui;
    Mode mode;
    QVector<bool> stations; //站点数组，存是否有站点需要传输数据
    QVector<int> data_len;  //每个站点的数据长度
    //计时、计数
    QTimer* timer;      //定时器
    QTime* TimeRecord;  //记录时间
    bool istimestart;   //是否开始计时
    int time_flag;      //数据发送计时
    int cur_pos;    //检测位置
    bool oneturn;   //一轮是否已经结束
    int send_num;   //一轮中需要发送数据的站点数量
    int lowest;
    int highest;
    //icon
    //QIcon*  DataReady;

    //按钮颜色设置
    QPalette default_pal;
    QPalette pal;

    QVector<QPushButton*> mybtn;        //指针数组，指向站点的按钮
    QVector<QLabel*> len_label;
    QString res;                        //每次发送的结果
    //函数
    void stations_clear();
};

#endif // SHOWBITMAP_H
