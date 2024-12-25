#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include <QMainWindow>
#include "trobotmotion.h"
#include "trobotmodel.h"
#include "vars.h"

namespace Ui {
class TMainWindow;
}

class TMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    int motion_type;
    int speed;
    int step;

    QVector<float> coord;

    TRobotMotion *MotionThread;

    //геометрическая модель робота
    TRobotModel *RobotModel;

    explicit TMainWindow(QWidget *parent = 0);
    ~TMainWindow();

private slots:

    void on_pushButton_x_plus_clicked();

    void on_pushButton_x_minus_clicked();

    void on_pushButton_y_plus_clicked();

    void on_pushButton_y_minus_clicked();

    void on_pushButton_z_minus_clicked();

    void on_pushButton_z_plus_clicked();

    void on_spinBox_Step_valueChanged(int arg1);

    void on_pushButton_rx_plus_clicked();

    void on_pushButton_rx_minus_clicked();

    void on_pushButton_ry_plus_clicked();

    void on_pushButton_ry_minus_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_XY_PLane_clicked();

    void on_pushButton_YZ_Plane_clicked();

    void on_pushButton_XZ_PLane_clicked();

    void on_spinBox_JT1_valueChanged(int arg1);

    void on_spinBox_JT2_valueChanged(int arg1);

    void on_spinBox_JT3_valueChanged(int arg1);

    void on_spinBox_JT4_valueChanged(int arg1);

    void on_spinBox_JT5_valueChanged(int arg1);

    void on_spinBox_JT6_valueChanged(int arg1);

public slots:
    void updatePos(QString pos);

private:
    Ui::TMainWindow *ui;
};

#endif // TMAINWINDOW_H
