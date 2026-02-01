#ifndef AUTOSCANERLFORM_H
#define AUTOSCANERLFORM_H

#include <QWidget>
#include <QVector3D>
#include "robotmotion.h"
#include <QCloseEvent>
#include <QShowEvent>

//класс инкаписулируший автоматическое управление сканированием обьекта по модели обьекта

namespace Ui {
class AutoScanerlForm;
}

class AutoScanerlForm : public QWidget
{
    Q_OBJECT

public:
    explicit AutoScanerlForm(QWidget *parent = nullptr);
    ~AutoScanerlForm();

    void UpdateState();

    void setObjMotion(RobotMotion *obj);
    void setStartPoint(QVector3D pt) {mStartPoint = pt;}
    void setDirVec(QVector3D pt) {mDirVector = pt;}
    void setRad(float rad) {mRad = rad;}
    void setAngle(float angle) {mStartAngle = angle;}

    QVector3D startPoint() {return mStartPoint;}
    QVector3D dirVec() {return  mDirVector;}
    float rad() {return mRad;}
    float angle() {return  mStartAngle;}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Check_clicked();

private:
    Ui::AutoScanerlForm *ui;

    //здеьс булет хранится модель сканирвоания

    //начальная точка таректоррии
    QVector3D mStartPoint;
    //единичный веторо траектории сканирования
    QVector3D mDirVector;
    //радисус кривизны
    float mRad;
    //уголв ввода
    float mStartAngle;
    RobotMotion *m_RobotMotion;

    //флаг проверки пармаетров сканирования
    bool mCorrectParams;
    //проверка точек траектороии

    bool mUpdateVars = false;

    //void checkTargetPoints();
    void startScan();
    void checkConfiguration();
};

#endif // AUTOSCANERLFORM_H
