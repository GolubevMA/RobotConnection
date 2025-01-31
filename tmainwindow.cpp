#include "tmainwindow.h"
#include "ui_tmainwindow.h"
#include "qdebug.h"
#include "tpointdialog.h"
#include <QSettings>
#include "stepfile.h"
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TMainWindow)
{   
    step = 5;


    ExpressSchema *schema = new ExpressSchema("J://WorkProjects//RobotConnection//debug//ap203.exp");
    StepFile stepFile("J://WorkProjects//RobotConnection//debug//sample02.step", schema);


    RobotMotion = new TRobotMotion(this, "192.168.0.1");
    RobotMotion->Terminate = false;
    RobotMotion->start();


    RobotModel = new TRobotModel();
    RobotModel->loadModel();

    ui->setupUi(this);

    //connect(RobotMotion, SIGNAL(updatePos(QString)), this, SLOT(updatePos(QString)));
    connect(RobotMotion, SIGNAL(UpdateSystemState()), this ,SLOT(UpdateSystemState()));
    connect(RobotMotion, SIGNAL(calcAngle()), this, SLOT(calcAngles()));

    ui->widget_Robot->SetRobotModel(RobotModel);

    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };
    for (int i = 6; i < MAX_AXIS_COUNT;  i++) {
        axisis[i]->setVisible(false);
    }
}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
    RobotMotion->Terminate = true;
    RobotMotion->terminate();
    delete RobotMotion;
    delete RobotModel;
    delete ui;
}
//------------------------------------------------------------------------------
void TMainWindow::showEvent(QShowEvent  *event)
{
    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    //грузим значения праматров ui
    QSettings sett(QApplication::organizationName(), QApplication::applicationName());

    sett.beginGroup("MainForm");
    int spin_count = sett.value("spin_box_cnt", MAX_AXIS_COUNT).toInt();
    for (int i = 0; i < spin_count; i++) {
        axisis[i]->setText(sett.value(QString("spin_box_%1").arg(i), 30).toString());
    }
    ui->spinBox_Step->setValue(sett.value("step",10).toFloat());
    sett.endGroup();

}
//------------------------------------------------------------------------------
void TMainWindow::closeEvent(QCloseEvent *event)
{
    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    //грузим значения праматров ui
    QSettings sett(QApplication::organizationName(), QApplication::applicationName());
    sett.beginGroup("MainForm");
    sett.setValue("spin_box_cnt",RobotMotion->AxisCount);
    for (int i = 0; i < RobotMotion->AxisCount; i++) {
        sett.setValue(QString("spin_box_%1").arg(i), axisis[i]->text().toFloat());
    }
    sett.setValue("step",ui->spinBox_Step->value());
    sett.endGroup();
}

//------------------------------------------------------------------------------
//обновляем состояние графичексого интерфейса в соотвевсие с состоянием робота
//------------------------------------------------------------------------------
void TMainWindow::UpdateSystemState()
{
    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    UpdateVarsFlag = true;

    ui->comboBox->setCurrentIndex(RobotMotion->MotionMode - 1);
    if (RobotMotion->MotionMode == TRobotMotion::MotioType::JOIUNT)
    {
        for (int i = 0; i < RobotMotion->AxisCount; i++) {
            axisis[i]->setText(QString::number(RobotMotion->coord_jt.at(i)));
        }
    }
    else {
        for (int i = 0; i < RobotMotion->AxisCount; i++) {
            axisis[i]->setText(QString::number(RobotMotion->coord_xyz.at(i)));
        }
    }


    UpdateVarsFlag = false;
}
//------------------------------------------------------------------------------
//определям углы на которые нужно повернуть детали робота
//------------------------------------------------------------------------------
void TMainWindow::calcAngles()
{
//    QList<float>axises;
//    axises.append(RobotMotion->coord_jt);
//    axises[2] += 90;
    //отрисовыаем двидение робота
    //ui->widget_Robot->SetRobotRotation(axises);


//    int sep_ind = angle.indexOf(";");
//    QString jt_pos = angle.mid(0, sep_ind);

//    float jt_coord[MAX_AXIS_COUNT];
//    int cnt = 0;
//    int seek_pos = 1;
//    int ind = jt_pos.indexOf(",", seek_pos);
//    while (ind > 0)
//    {
//        QString num = jt_pos.mid(seek_pos -1, ind - seek_pos);
//        //добвлаем уго в массив координат
//        jt_coord[cnt] = num.toFloat();
//        seek_pos = ind + 2;
//        ind = jt_pos.indexOf(",", seek_pos);
//        cnt++;
//    }
//    jt_coord[2] += 90;
//    //отрисовыаем двидение робота
//    ui->widget_Robot->SetRobotRotation(jt_coord, ++cnt);
}
//------------------------------------------------------------------------------
void TMainWindow::on_comboBox_activated(int index)
{
    if (!UpdateVarsFlag)
    {
        RobotMotion->MotionMode =  index+1;
        UpdateSystemState();
    }
}
//------------------------------------------------------------------------------
//проверяем ответ на команду
//------------------------------------------------------------------------------
void TMainWindow::cherResonse(int code)
{
    QString msg = "Motion Error : ";
    if (code < 0)
    {
        switch (code) {
        case  TRobotMotion::MotioCmdError::NotFound :
            msg += "cmd not found";
            break;
        case  TRobotMotion::MotioCmdError::ConnetionError :
            msg += " timeout error ";
            break;
        case  TRobotMotion::MotioCmdError::Range :
            msg += " rnage error ";
            break;
        default:
            break;
        }
        QMessageBox::warning(this, "MotionCmd", msg);
    }
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_x_plus_clicked()
{    
    QString satte;
    cherResonse(RobotMotion->StepMove(1, step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_x_minus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(1, -step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_y_plus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(2, step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_y_minus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(2, -step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_z_minus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(3, -step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_z_plus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(3, step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rx_plus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(4, -step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rx_minus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(4, step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_ry_plus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(5, -step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_ry_minus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(5, step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rz_plus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(6, step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rz_minus_clicked()
{
    QString satte;
    cherResonse(RobotMotion->StepMove(6, -step, satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_Step_valueChanged(int arg1)
{
    step = arg1;
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_Move_clicked()
{
    QList<float> pt;
    if(RobotMotion->MotionMode  == TRobotMotion::MotioType::JOIUNT) {
        pt.append( RobotMotion->coord_jt);
    }
    else {
        pt.append( RobotMotion->coord_xyz);
    }

    TPointDialog dialog(this);
    if (dialog.Run(&pt, MAX_AXIS_COUNT) == QDialog::Accepted)
    {
        QString state;
        cherResonse(RobotMotion->MovePoint(pt, state));
    }
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_clicked()
{
    QString satte;
    cherResonse(RobotMotion->DepartMove(ui->doubleSpinBox_Depart->value(), satte));
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_ZERO_clicked()
{
    QString satte;
    cherResonse(RobotMotion->SetZero(satte));
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
void TMainWindow::on_pushButton_CMD_clicked()
{
    //менем ск
    RobotMotion->MotionMode = TRobotMotion::MotioType::BASE;
    UpdateSystemState();

    QString satte;
    cherResonse(RobotMotion->StepMove(2, 150, satte)); //Y
    cherResonse(RobotMotion->StepMove(3, 150, satte)); //Z
//    cherResonse(RobotMotion->StepMove(2, -150, satte)); //-Y
//    cherResonse(RobotMotion->StepMove(3, -150, satte)); // -Z

}
//------------------------------------------------------------------------------
//void TMainWindow::on_spinBox_JT1_valueChanged(int arg1)
//{
//    coord[0] = arg1;
//    ui->widget_Robot->SetRobotRotation(coord);
//}
////------------------------------------------------------------------------------
//void TMainWindow::on_spinBox_JT2_valueChanged(int arg1)
//{
//    coord[1] = arg1;
//    ui->widget_Robot->SetRobotRotation(coord);
//}
////------------------------------------------------------------------------------
//void TMainWindow::on_spinBox_JT3_valueChanged(int arg1)
//{
//    coord[2] = arg1;
//    ui->widget_Robot->SetRobotRotation(coord);
//}
////------------------------------------------------------------------------------
//void TMainWindow::on_spinBox_JT4_valueChanged(int arg1)
//{
//    coord[3] = arg1;
//    ui->widget_Robot->SetRobotRotation(coord);
//}
////------------------------------------------------------------------------------
//void TMainWindow::on_spinBox_JT5_valueChanged(int arg1)
//{
//    coord[4] = arg1;
//    ui->widget_Robot->SetRobotRotation(coord);
//}
////------------------------------------------------------------------------------
//void TMainWindow::on_spinBox_JT6_valueChanged(int arg1)
//{
//    coord[5] = arg1;
//    ui->widget_Robot->SetRobotRotation(coord);
//}


