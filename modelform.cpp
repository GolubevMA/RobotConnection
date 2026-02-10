#include "modelform.h"
#include "ui_modelform.h"
#include "vars.h"
#include "qdebug.h"
#include "QMessageBox"
//------------------------------------------------------------------------------
ModelForm::ModelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelForm)
{
    ui->setupUi(this);
}
//------------------------------------------------------------------------------
ModelForm::~ModelForm()
{
    delete ui;
}
//------------------------------------------------------------------------------
//загрузака модели
//------------------------------------------------------------------------------
void ModelForm::createModel()
{
    QVector3D start;
    start.setX(ui->spinBoxStartX->value());
    start.setY(ui->spinBoxStartY->value());
    start.setZ(ui->spinBoxStartZ->value());
    SelectedModel->setStartPoint(start);

    QVector3D vdir;
    vdir.setX(ui->spinBoxEndX->value());
    vdir.setY(ui->spinBoxEndY->value());
    vdir.setZ(ui->spinBoxEndZ->value());
    SelectedModel->setDirVec(vdir);

    SelectedModel->setRad(ui->spinBoxRad->value());
    SelectedModel->setAngle(ui->spinBoxAngle->value());

    //фомриурем траекторрию
    QList<DecartPoint> pts;

    //шаг  сканирования
    float step = 1.0f;
    //угол ввода
    float enter_angle = -SelectedModel->angle() * M_PI / 180;
    //определяеем напрявление сканирования - прямое направление - скан от ближней точки к дальней
    bool dir = vdir.x() > 0 || vdir.y() > 0;
    qDebug() << " dir " << dir;

    //расчет коордниат в локальной плоскости XY, где x - координата вдоль вектора dirVec. z -  коордиата по оси
    float x_start = 0;
    float x0 = -SelectedModel->rad() * sin(enter_angle);
    float y0 = -SelectedModel->rad() * cos(enter_angle);
    float track_length = 2 * x0;

    qDebug() << " x0 " << x0 << "rad " << SelectedModel->rad();

    float x = x_start;
    while (x < track_length)
    {
        //считаем у по уравнению дуги
        float y = -SelectedModel->rad() * cos(enter_angle) + powf(powf(SelectedModel->rad(),2) - powf(x + SelectedModel->rad() * sin(enter_angle),2),0.5);
        //счтаем theta
        float theta = atan2(y-y0,x-x0)*180/M_PI;
        //выбирвем угол в завимисти от коордитанты и напраления
        if ((dir && x < x0) || (!dir && x > x0)) theta = 270.0f - theta;
        else theta += 90.0f;

        //формриуем точку
        float dx = x * fabs(vdir.x()) / vdir.length();
        float dy = x * fabs(vdir.y()) / vdir.length();

        DecartPoint pt;
        pt.setX(dir ?  dx :  - dx);
        pt.setY(dir ?  dy :  - dy);
        pt.setZ(y);
        pt.setO((dir && x < x0) || (!dir && x > x0) ? 90 : -90);
        pt.setA(theta);
        pt.setT(0);
        pts.append(pt);
        x++;
    }
    SelectedModel->setTarckList(pts);

    QMessageBox::critical(this, tr("Model"),tr("Model updatd"));
}
//------------------------------------------------------------------------------
//обновим ui
//------------------------------------------------------------------------------
void ModelForm::updateState()
{
    mUpdateVars = true;

    ui->spinBoxStartX->setValue(SelectedModel->startPt().x());
    ui->spinBoxStartY->setValue(SelectedModel->startPt().y());
    ui->spinBoxStartZ->setValue(SelectedModel->startPt().z());

    ui->spinBoxEndX->setValue(SelectedModel->dirVec().x());
    ui->spinBoxEndY->setValue(SelectedModel->dirVec().y());
    ui->spinBoxEndZ->setValue(SelectedModel->dirVec().z());

    ui->spinBoxRad->setValue(SelectedModel->rad());
    ui->spinBoxAngle->setValue(SelectedModel->angle());

    mUpdateVars = false;
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxEndX_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        QVector3D stp = SelectedModel->dirVec();
        stp.setX(arg1);
        SelectedModel->setDirVec(stp);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxEndY_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        QVector3D stp = SelectedModel->dirVec();
        stp.setY(arg1);
        SelectedModel->setDirVec(stp);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxEndZ_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        QVector3D stp = SelectedModel->dirVec();
        stp.setZ(arg1);
        SelectedModel->setDirVec(stp);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxStartX_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        QVector3D stp = SelectedModel->startPt();
        stp.setX(arg1);
        SelectedModel->setStartPoint(stp);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxStartY_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        QVector3D stp = SelectedModel->startPt();
        stp.setY(arg1);
        SelectedModel->setStartPoint(stp);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxStartZ_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        QVector3D stp = SelectedModel->startPt();
        stp.setZ(arg1);
        SelectedModel->setStartPoint(stp);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxRad_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        SelectedModel->setRad(arg1);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_spinBoxAngle_valueChanged(double arg1)
{
    if (!mUpdateVars)
    {
        SelectedModel->setAngle(arg1);
    }
}
//------------------------------------------------------------------------------
void ModelForm::on_pushButton_clicked()
{
    createModel();
}
