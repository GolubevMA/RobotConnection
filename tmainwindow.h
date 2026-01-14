#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include <QMainWindow>
#include "robotmotion.h"
#include "vars.h"
#include <QShowEvent>
#include <QCloseEvent>
#include "formremote.h"
#include "trobotmotionthread.h"

namespace Ui {
class TMainWindow;
}

class TMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //обьект упровения роботом
    RobotMotion *m_RobotMotion;
    //обьект графического предсталения робота
    ControlSystemModel *CSystemModel;

    //TRobotMotionThread *m_Mtread;

    QList<float> test;

    QTimer *updateTimer;

    explicit TMainWindow(QWidget *parent = 0);
    ~TMainWindow();

    void cherResonse(int code);

    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

    void LoadRobotModel(QString step_name);

private slots:

    void on_spinBox_JT1_valueChanged(int arg1);
    void on_spinBox_JT2_valueChanged(int arg1);
    void on_spinBox_JT3_valueChanged(int arg1);
    void on_spinBox_JT4_valueChanged(int arg1);
    void on_spinBox_JT5_valueChanged(int arg1);
    void on_spinBox_JT6_valueChanged(int arg1);

    void on_pushButton_conn_clicked();
    void on_pushButton_Remote_clicked(bool checked);

public slots :
    void UpdateSystemState();

private:
    Ui::TMainWindow *ui;
};

#endif // TMAINWINDOW_H
