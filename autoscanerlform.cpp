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
