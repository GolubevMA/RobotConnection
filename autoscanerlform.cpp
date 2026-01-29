#include "autoscanerlform.h"
#include "ui_autoscanerlform.h"
#include "qdebug.h"
#include "decartpoint.h"
#include <QSettings>
#include "QMessageBox"
//------------------------------------------------------------------------------
AutoScanerlForm::AutoScanerlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoScanerlForm)
//------------------------------------------------------------------------------
{    
    mCorrectParams = false;
    m_RobotMotion = NULL;
    mUpdateVars = false;

    ui->setupUi(this);
}
//------------------------------------------------------------------------------
AutoScanerlForm::~AutoScanerlForm()
{
    delete ui;
}
//------------------------------------------------------------------------------
//обновим ui
//------------------------------------------------------------------------------
void AutoScanerlForm::UpdateState()
{
    mUpdateVars = true;

    ui->spinBoxStartX->setValue(mStartPoint.x());
    ui->spinBoxStartY->setValue(mStartPoint.y());
    ui->spinBoxStartZ->setValue(mStartPoint.z());

    ui->spinBoxEndX->setValue(mDirVector.x());
    ui->spinBoxEndY->setValue(mDirVector.y());
    ui->spinBoxEndZ->setValue(mDirVector.z());

    ui->spinBoxRad->setValue(mRad);
    ui->spinBoxAngle->setValue(mStartAngle);

    mUpdateVars = false;
}
//------------------------------------------------------------------------------
void AutoScanerlForm::setObjMotion(RobotMotion *obj)
{
    m_RobotMotion = obj;
    //connect(m_RobotMotion, SIGNAL(buildStarted()), this, SLOT(UpdateTrack()), Qt::QueuedConnection);
}
//------------------------------------------------------------------------------
void AutoScanerlForm::checkScanAction()
{

}
//------------------------------------------------------------------------------
//обновлем параметры дуги и проверям начальуню точку
//------------------------------------------------------------------------------
void AutoScanerlForm::checkConfiguration()
{
    mStartPoint.setX(ui->spinBoxStartX->value());
    mStartPoint.setY(ui->spinBoxStartY->value());
    mStartPoint.setZ(ui->spinBoxStartZ->value());

    mDirVector.setX(ui->spinBoxEndX->value());
    mDirVector.setY(ui->spinBoxEndY->value());
    mDirVector.setZ(ui->spinBoxEndZ->value());

    mRad = ui->spinBoxRad->value();
    mStartAngle = ui->spinBoxAngle->value();

    DecartPoint pt;
    pt.setXyz(mStartPoint);
    bool dir = mDirVector.x() > 0 || mDirVector.y() > 0;
    pt.setO(dir ? 90 : -90);
    pt.setA(dir ? 270 - mStartAngle : 90 + mStartAngle);
    pt.setT(0);

    int res = m_RobotMotion->checkPtIsValid(pt);
    if (res) {
        mCorrectParams = true;
        QMessageBox::information(this, "Check prams", "Params correct");
    }
    else QMessageBox::critical(this, "Check prams", "Point ureacheble " + QString::number(res));
}
//------------------------------------------------------------------------------
//запуск сканирвоания образца
//------------------------------------------------------------------------------
void AutoScanerlForm::startScan()
{
    if  (mCorrectParams)
    {
        //фомриурем траекторрию
        QList<DecartPoint> pts;

        //шаг  сканирования
        float step = 1.0f;
        //угол ввода
        float enter_angle = -mStartAngle * M_PI / 180;
        //определяеем напрявление сканирования - прямое направление - скан от ближней точки к дальней
        bool dir = mDirVector.x() > 0 || mDirVector.y() > 0;
        qDebug() << " dir " << dir;

        //расчет коордниат в локальной плоскости XY, где x - координата вдоль вектора dirVec. z -  коордиата по оси
        float x_start = 0;
        float x0 = -mRad * sin(enter_angle);
        float y0 = -mRad* cos(enter_angle);
        float track_length = 2 * x0;

        qDebug() << " x0 " << x0 << "rad " << mRad;

        float x = x_start;
        while (x < track_length)
        {
            //считаем у по уравнению дуги
            float y = -mRad * cos(enter_angle) + powf(powf(mRad,2) - powf(x + mRad * sin(enter_angle),2),0.5);
            //счтаем theta
            float theta = atan2(y-y0,x-x0)*180/M_PI;
            //выбирвем угол в завимисти от коордитанты и напраления
            if ((dir && x < x0) || (!dir && x > x0)) theta = 270.0f - theta;
            else theta += 90.0f;


            //формриуем точку
            float dx = x * fabs(mDirVector.x()) / mDirVector.length();
            float dy = x * fabs(mDirVector.y()) / mDirVector.length();

            DecartPoint pt;
            pt.setX(dir ? mStartPoint.x() + dx : mStartPoint.x() - dx);
            pt.setY(dir ? mStartPoint.y() + dy : mStartPoint.y() - dy);
            pt.setZ(mStartPoint.z() + y);
            pt.setO((dir && x < x0) || (!dir && x > x0) ? 90 : -90);
            pt.setA(theta);
            pt.setT(0);
            pts.append(pt);

            x++;
        }
        qDebug() << "build ned";
        if (!m_RobotMotion->ParseTrackXyz(pts, 50)) {
            QMessageBox::critical(this, "Scan Track", "Some Point out of range!");
        }
    }
}
//------------------------------------------------------------------------------
void AutoScanerlForm::on_pushButton_clicked()
{
    startScan();
}
//---------------------------------------------------------------------------
void AutoScanerlForm::on_pushButton_Check_clicked()
{
    checkConfiguration();
}
//---------------------------------------------------------------------------
//void AutoScanerlForm::
//{
//    bool res = false;
//    if (m_objMotion->autopilotCmdEnable())
//    {
//        if(m_objMotion->steerState() != STEER_LEFT) {
//            BLOG(LCH) << " TO LEFT ";
//            res = true; m_objMotion->toLeft();
//        }
//    }
//}
//---------------------------------------------------------------------------
