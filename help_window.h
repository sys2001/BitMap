#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H

#include <QDialog>

namespace Ui {
class help_window;
}

class help_window : public QDialog
{
    Q_OBJECT

public:
    explicit help_window(QWidget *parent = nullptr);
    ~help_window();

private:
    Ui::help_window *ui;
};

#endif // HELP_WINDOW_H
