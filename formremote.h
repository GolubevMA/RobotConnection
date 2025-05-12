#ifndef FORMREMOTE_H
#define FORMREMOTE_H

#include <QWidget>
#include "robotmotion.h"
#include "vars.h"
#include <QDialog>
#include <QTimer>

namespace Ui {
class FormRemote;
}

class FormRemote : public QWidget
{
    Q_OBJECT

public:

    int speed;
    int step;
    int  MotionMode;
    bool UpdateVarsFlag;

    explicit FormRemote(QWidget *parent = nullptr);
    ~FormRemote();

    void setObjMotion(RobotMotion * obj);

private:

    //обьект упровения роботом
    RobotMotion *m_RobotMotion;

    QTimer *updateTimer;

    Ui::FormRemote *ui;

private slots :


    void on_spinBox_Step_valueChanged(int arg1);
    void on_comboBox_activated(int index);
    void on_pushButton_Move_clicked();
    void on_pushButton_clicked();
    void on_pushButton_ZERO_clicked();
    void on_pushButton_linear_clicked();
    void showEvent(QShowEvent  *event);
    void closeEvent(QCloseEvent *event);

public slots:

    //void updatePos(QString pos);
    void UpdateSystemState();

    void step_plus_clicked();
    void step_minus_clicked();
};



#endif // FORMREMOTE_H
