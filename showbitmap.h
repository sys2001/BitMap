#ifndef SHOWBITMAP_H
#define SHOWBITMAP_H

#include <QMainWindow>
#include <QVector>
#include <QMouseEvent>
#include "station.h"
#include "dialog.h"
#include "utils.h"
#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20
#define START_X 10
#define START_Y 20      
namespace Ui {
class showBitmap;
}


class showBitmap : public QMainWindow
{
    Q_OBJECT

public:
    explicit showBitmap(QWidget *parent = 0);
    ~showBitmap();
    
    void Init();            //初始化，显示
    void mousePressEvent(QMouseEvent*);
    
private slots:
    void on_station_triggered();

private:
    Ui::showBitmap *ui;
    Dialog * StationSettingWindows;         //站点设置窗
    Dialog * DelaySettingWindows;           //延时设置窗
    int Sta_Num;                //站点数
    int delay;              //每个站点的停留时间
    QVector<Station*> stations; //站点数组，存是否有站点需要传输数据
    
};

#endif // SHOWBITMAP_H
