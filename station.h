#ifndef STATION_H
#define STATION_H

#include <QPoint>
#include "utils.h"
class Station
{
public:
    Station();
    Station(QPoint pos);        //位置
    bool wait;                  //是否有数据等待发送
};

#endif // STATION_H
