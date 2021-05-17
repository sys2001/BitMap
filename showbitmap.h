#ifndef SHOWBITMAP_H
#define SHOWBITMAP_H

#include <QMainWindow>

namespace Ui {
class showBitmap;
}

class showBitmap : public QMainWindow
{
    Q_OBJECT

public:
    explicit showBitmap(QWidget *parent = 0);
    ~showBitmap();

private:
    Ui::showBitmap *ui;
};

#endif // SHOWBITMAP_H
