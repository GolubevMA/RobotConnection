#include "tmainwindow.h"
#include "ui_tmainwindow.h"
#include "qdebug.h"
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TMainWindow)
{   
    motion_type = 1;
    speed = 50;
    step = 5;
    coord = {0, 0, 0, 0, 0, 0};

    RobotModel = new TRobotModel();
    RobotModel->loadModel();

    MotionThread = new TRobotMotion(this, "192.168.0.1");
    MotionThread->Terminate = false;
    MotionThread->start();

    ui->setupUi(this);
    connect(MotionThread, SIGNAL(updatePos(QString)), this, SLOT(updatePos(QString)));

    //утсанвлиаем моедль в виждет
    ui->widget_Robot->SetRobotModel(RobotModel);

}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
    MotionThread->Terminate = true;
    MotionThread->terminate();

    delete MotionThread;
    delete RobotModel;
    delete ui;
}
//------------------------------------------------------------------------------
//обовляем координанту
//------------------------------------------------------------------------------
void TMainWindow::updatePos(QString pos)
{
    ui->plainTextEdit->appendPlainText(pos);
    int cnt = 0;

    int seek_pos = 1;
    int ind = pos.indexOf(",", seek_pos);
    while (ind > 0)
    {
        QString num = pos.mid(seek_pos -1, ind - seek_pos);
        //qDebug() << num;
        //добвлаем уго в массив координат
        coord[cnt] = num.toFloat();

        seek_pos = ind + 2;
        ind = pos.indexOf(",", seek_pos);
        cnt++;
    }
    coord[2] += 90;
    ui->widget_Robot->SetRobotRotation(coord);

}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_x_plus_clicked()
{    
    QString satte;
    if (MotionThread->StepMove(motion_type, 1, step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_x_minus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 1, -step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_y_plus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 2, step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_y_minus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 2, -step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_z_minus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 3, -step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_z_plus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 3, step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rx_plus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 4, -step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rx_minus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 4, step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_ry_plus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 5, -step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_ry_minus_clicked()
{
    QString satte;
    if (MotionThread->StepMove(motion_type, 5, step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_Step_valueChanged(int arg1)
{
    step = arg1;
}
//------------------------------------------------------------------------------
void TMainWindow::on_comboBox_activated(int index)
{
    motion_type = index+1;
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_XY_PLane_clicked()
{
   //ui->widget->
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_YZ_Plane_clicked()
{

}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_XZ_PLane_clicked()
{
    ui->widget_Robot->SetPlane(0);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT1_valueChanged(int arg1)
{
    coord[0] = arg1;
    ui->widget_Robot->SetRobotRotation(coord);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT2_valueChanged(int arg1)
{
    coord[1] = arg1;
    ui->widget_Robot->SetRobotRotation(coord);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT3_valueChanged(int arg1)
{
    coord[2] = arg1;
    ui->widget_Robot->SetRobotRotation(coord);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT4_valueChanged(int arg1)
{
    coord[3] = arg1;
    ui->widget_Robot->SetRobotRotation(coord);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT5_valueChanged(int arg1)
{
    coord[4] = arg1;
    ui->widget_Robot->SetRobotRotation(coord);
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_JT6_valueChanged(int arg1)
{
    coord[5] = arg1;
    ui->widget_Robot->SetRobotRotation(coord);
}
//------------------------------------------------------------------------------
