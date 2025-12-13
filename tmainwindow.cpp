    #include "tmainwindow.h"
#include "ui_tmainwindow.h"
#include "trobotmotionthread.h"
#include "qdebug.h"
#include <QSettings>
#include "stepfile.h"
#include "formremote.h"
#include <QMessageBox>
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

    //таймер обнвления ui
    updateTimer = new QTimer();
    updateTimer->start(30);

    ui->setupUi(this);

    ui->widget_Remote->setObjMotion(m_RobotMotion);
    ui->widget_Remote->setVisible(false);
    ui->widget_Robot->SetControlModel(CSystemModel);

    //connect(m_RobotMotion, SIGNAL(coordChanged()), this, SLOT(updateRobotCoord()));
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(UpdateSystemState()));
    connect(ui->widget_Remote, SIGNAL(UpdateTargetPoints(QList<QVector3D>&)), ui->widget_Robot, SLOT( SetTargetPoints(QList<QVector3D>&)));

}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
//    RobotMotion->Terminate = true;
//    RobotMotion->terminate();

    if (CSystemModel != NULL )delete CSystemModel;

    updateTimer->stop();
    delete updateTimer;
    delete ui;
}
//------------------------------------------------------------------------------
void TMainWindow::showEvent(QShowEvent  *event)
{
}
//------------------------------------------------------------------------------
void TMainWindow::closeEvent(QCloseEvent *event)
{
}
//------------------------------------------------------------------------------
//обновеям стостяние системы
//------------------------------------------------------------------------------
void TMainWindow::UpdateSystemState()
{
    ui->widget_Robot->SetRobotAngles(m_RobotMotion->GetCurrentJT());
    ui->label_freq->setText(QString::number(m_RobotMotion->GetFreq()));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_conn_clicked()
{
//    if (!m_RobotMotion->isConnected()) {
        qDebug() << "recc";
        m_RobotMotion->createConnection("192.168.0.1", 9015);
//    }

}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT1_valueChanged(int arg1)
{
    test[0] = arg1;
    ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT2_valueChanged(int arg1)
{
    test[1] = arg1;
    ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT3_valueChanged(int arg1)
{
    test[2] = arg1;
    ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT4_valueChanged(int arg1)
{
    test[3] = arg1;
    ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT5_valueChanged(int arg1)
{
    test[4] = arg1;
    ui->widget_Robot->SetRobotAngles(test);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT6_valueChanged(int arg1)
{
    test[5] = arg1;
    ui->widget_Robot->SetRobotAngles(test);
}
//-----------------------------------------------------------------------------
//форма ручного упрвления
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_Remote_clicked(bool checked)
{
    ui->widget_Remote->setVisible(checked);
}
//------------------------------------------------------------------------------
