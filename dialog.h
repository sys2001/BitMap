#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include "utils.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_ack_clicked();

    void on_back_clicked();

private:
    Ui::Dialog *ui;
    QString msg;            //占位信息

};

#endif // DIALOG_H
