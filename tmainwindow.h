#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include <QMainWindow>
#include "tconnectionthread.h"

namespace Ui {
class TMainWindow;
}

class TMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TConnectionThread *cPthrd;

    explicit TMainWindow(QWidget *parent = 0);
    ~TMainWindow();

private slots:

    void on_pushButton_x_plus_clicked();

    void on_pushButton_x_minus_clicked();

    void on_pushButton_y_plus_clicked();

    void on_pushButton_y_minus_clicked();

    void on_pushButton_z_minus_clicked();

    void on_pushButton_z_plus_clicked();

private:
    Ui::TMainWindow *ui;
};

#endif // TMAINWINDOW_H
