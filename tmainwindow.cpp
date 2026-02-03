#include "tmainwindow.h"
#include "ui_tmainwindow.h"
#include "trobotmotionthread.h"
#include "qdebug.h"
#include <QSettings>
#include "formremote.h"
#include <QMessageBox>
#include <QSettings>
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TMainWindow)
{   

    CSystemModel = NULL;

    //грузим модель
    CSystemModel = new ControlSystemModel();
    CSystemModel->LoadSystemModel("J:\\WorkProjects\\RobotConnection\\RS007N-BC01.stp");
    //CSystemModel->LoadSystemModel("J:\\WorkProjects\\RoboScan\\RobotConnection\\RS007N-BC01_mod.STEP");
    test = {0,0,0,0,0,0};

    m_RobotMotion = new RobotMotion();
    //отруваем соедининиеме
    bool conn = m_RobotMotion->createConnection("192.168.0.1", 9015);

    //фомриуем обьект сканирования
    m_ScanController = new AutoScanController(m_RobotMotion, this);

    //таймер обнвления ui
    updateTimer = new QTimer();
    updateTimer->start(30);

    ui->setupUi(this);

    ui->widget_Remote->setObjMotion(m_RobotMotion);
    //ui->widget_Remote->setVisible(false);
    ui->widget_Robot->SetControlModel(CSystemModel);
    ui->widget_AutoScan->setControlller(m_ScanController);
    ui->widget_Voice->setRobotObject(m_RobotMotion);

    connect(m_RobotMotion, SIGNAL(coordChanged()), this, SLOT(updateRobotCoord()));
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(UpdateSystemState()));
    connect(ui->widget_Remote, SIGNAL(UpdateTargetPoints(QList<QVector3D>&)), ui->widget_Robot, SLOT( SetTargetPoints(QList<QVector3D>&)));

}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
    if (CSystemModel != NULL )delete CSystemModel;
    updateTimer->stop();
    delete updateTimer;
    delete ui;
    delete m_RobotMotion;
}
//------------------------------------------------------------------------------
void TMainWindow::showEvent(QShowEvent  *event)
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    settings.beginGroup("MainForm");
    setGeometry(settings.value("geometry", QRect(100, 100, 1200, 800)).toRect());
    ui->splitter->restoreState(settings.value("splitter").toByteArray());
    ui->splitter_2->restoreState(settings.value("splitter_2").toByteArray());
    ui->splitter_3->restoreState(settings.value("splitter_3").toByteArray());
    settings.endGroup();
    settings.beginGroup("AutoScanerForm");
    float sx = settings.value("StartPointX",QVariant(0)).toFloat();
    float sy = settings.value("StartPointY",QVariant(400)).toFloat();
    float sz = settings.value("StartPointZ",QVariant(-340)).toFloat();
    ui->widget_AutoScan->setStartPoint(QVector3D(sx,sy,sz));
    sx = settings.value("mDirVectorX",QVariant(0)).toFloat();
    sy = settings.value("mDirVectorY",QVariant(480)).toFloat();
    sz = settings.value("mDirVectorZ",QVariant(-340)).toFloat();
    ui->widget_AutoScan->setDirVec(QVector3D(sx,sy,sz));
    ui->widget_AutoScan->setRad(settings.value("rad",QVariant(80)).toFloat());
    ui->widget_AutoScan->setAngle(settings.value("angle",QVariant(80)).toFloat());
    settings.endGroup();

    ui->widget_AutoScan->UpdateState();
}
//------------------------------------------------------------------------------
void TMainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "cploding";
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    settings.beginGroup("MainForm");
    settings.setValue("geometry", geometry());
    settings.setValue("splitter", ui->splitter->saveState());
    settings.setValue("splitter_2", ui->splitter_2->saveState());
    settings.setValue("splitter_3", ui->splitter_3->saveState());
    settings.endGroup();
    settings.beginGroup("AutoScanerForm");
    QVector3D sp = ui->widget_AutoScan->startPoint();
    settings.setValue("StartPointX",sp.x());
    settings.setValue("StartPointY",sp.y());
    settings.setValue("StartPointZ",sp.z());
    QVector3D dp = ui->widget_AutoScan->dirVec();
    settings.setValue("mDirVectorX",dp.x());
    settings.setValue("mDirVectorY",dp.y());
    settings.setValue("mDirVectorZ",dp.z());
    settings.setValue("rad",ui->widget_AutoScan->rad());
    settings.setValue("angle",ui->widget_AutoScan->angle());
    settings.endGroup();
}
//------------------------------------------------------------------------------
//обновеям стостяние системы
//------------------------------------------------------------------------------
void TMainWindow::UpdateSystemState()
{
    ui->widget_Robot->SetRobotAngles(m_RobotMotion->GetCurrentJT());
    ui->label_freq->setText(QString::number(m_RobotMotion->GetFreq(), 'f', 1));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_conn_clicked()
{
    //if (!m_RobotMotion->isConnected()) {
        qDebug() << "recc";
        m_RobotMotion->createConnection("192.168.0.1", 9015);
    //}
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT1_valueChanged(int arg1)
{
    //test[0] = arg1;
    //ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT2_valueChanged(int arg1)
{
    //test[1] = arg1;
    //ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT3_valueChanged(int arg1)
{
    //test[2] = arg1;
    //ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT4_valueChanged(int arg1)
{
    //test[3] = arg1;
    //ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT5_valueChanged(int arg1)
{
    //test[4] = arg1;
    //ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT6_valueChanged(int arg1)
{
    //test[5] = arg1;
    //ui->widget_Robot->SetRobotAngles(test);
}
//-----------------------------------------------------------------------------
//форма ручного упрвления
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_Remote_clicked(bool checked)
{
    //ui->widget_Remote->setVisible(checked);
}
//------------------------------------------------------------------------------
