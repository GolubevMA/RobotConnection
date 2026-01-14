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
    void showEvent(QShowEvent  *event) override;
    void closeEvent(QCloseEvent *event) override;

private:

    //обьект упровения роботом
    RobotMotion *m_RobotMotion;    
    QTimer *updateTimer;

    //список точек JT траеткории
    QList<JTPoint> m_TrackJtPoints;

    //спискок точек траектории в базисе XYZ
    QList<QVector3D> m_TrackPoints;
    //угол между поверхностью и схватом
    QList<float> m_TrackAngles;

    //массим плосокостей точек траектории
    //QList<EulerAngles> m_TrackPlanes;


    //текущая точка
    int CurrentPoint;

    Ui::FormRemote *ui;

    void UpdateTable();

private slots :


    void on_spinBox_Step_valueChanged(int arg1);
    void on_comboBox_activated(int index);
    void on_pushButton_Move_clicked();
    void on_pushButton_clicked();
    void on_pushButton_ZERO_clicked();    
    void on_pushButton_linear_clicked(bool checked);
    void on_pushButton_addPt_clicked();
    void on_pushButton_RemovePt_clicked();
    void on_pushButton_ChangePt_clicked();
    //void on_tableWidget_points_cellClicked(int row, int column);
    void on_pushButton_MoveArc_clicked();
    void on_pushButton_BuildStart_clicked();
    void on_pushButton_BuildStop_clicked();

public slots:

    //void updatePos(QString pos);
    void UpdateSystemState();
    void step_plus_clicked();
    void step_minus_clicked();
    void UpdateTrack();

signals :
    void UpdateTargetPoints(QList<QVector3D> &lst);
};



#endif // FORMREMOTE_H
