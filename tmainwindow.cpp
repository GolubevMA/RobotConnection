#include "tmainwindow.h"
#include "ui_tmainwindow.h"
#include "qdebug.h"
#include <QSettings>
//------------------------------------------------------------------------------
const int MAX_AXIS_COUNT = 7;
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TMainWindow)
{   
    step = 5;

    RobotModel = new TRobotModel();
    RobotModel->loadModel();

    RobotMotion = new TRobotMotion(this, "192.168.0.1", RobotModel->DetalCount);
    RobotMotion->Terminate = false;
    RobotMotion->start();

    ui->setupUi(this);
    connect(RobotMotion, SIGNAL(updatePos(QString)), this, SLOT(updatePos(QString)));
    //утсанвлиаем моедль в виждет
    ui->widget_Robot->SetRobotModel(RobotModel);

    QSpinBox *axisis[MAX_AXIS_COUNT] = {ui->spinBox_X, ui->spinBox_Y,
        ui->spinBox_Z, ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz, ui->spinBox_reserv
    };
    for (int i = RobotMotion->AxisCount; i < MAX_AXIS_COUNT;  i++) {
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
    QSpinBox *axisis[MAX_AXIS_COUNT] = {ui->spinBox_X, ui->spinBox_Y,
        ui->spinBox_Z, ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz, ui->spinBox_reserv
    };

    //грузим значения праматров ui
    QSettings sett(QApplication::organizationName(), QApplication::applicationName());

    sett.beginGroup("MainForm");
    int spin_count = sett.value("spin_box_cnt", MAX_AXIS_COUNT).toInt();
    for (int i = 0; i < spin_count; i++) {
        axisis[i]->setValue(sett.value(QString("spin_box_%1").arg(i), 30).toFloat());
    }
    ui->spinBox_Step->setValue(sett.value("step",10).toFloat());
    sett.endGroup();

}
//------------------------------------------------------------------------------
void TMainWindow::closeEvent(QCloseEvent *event)
{
    QSpinBox *axisis[MAX_AXIS_COUNT] = {ui->spinBox_X, ui->spinBox_Y,
        ui->spinBox_Z, ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz, ui->spinBox_reserv
    };

    //грузим значения праматров ui
    QSettings sett(QApplication::organizationName(), QApplication::applicationName());
    sett.beginGroup("MainForm");
    sett.setValue("spin_box_cnt",RobotMotion->AxisCount);
    for (int i = 0; i < RobotMotion->AxisCount; i++) {
        sett.setValue(QString("spin_box_%1").arg(i), axisis[i]->value());
    }
    sett.setValue("step",ui->spinBox_Step->value());
    sett.endGroup();
}
//------------------------------------------------------------------------------
//обовляем координанту
//------------------------------------------------------------------------------
void TMainWindow::updatePos(QString pos)
{

    int sep_ind = pos.indexOf(";");
    QString jt_pos = pos.mid(0, sep_ind);
    QString xyz_pos = pos.mid(sep_ind + 1, pos.length() - sep_ind);
    //qDebug() << "jt "<< jt_pos << " xsxx " << xyz_pos;

    ui->plainTextEdit->appendPlainText("JT " + jt_pos);
    ui->plainTextEdit->appendPlainText("XYZ " + xyz_pos);

    float jt_coord[MAX_AXIS_COUNT];
    int cnt = 0;
    int seek_pos = 1;    
    int ind = jt_pos.indexOf(",", seek_pos);
    while (ind > 0)
    {
        QString num = jt_pos.mid(seek_pos -1, ind - seek_pos);
        //добвлаем уго в массив координат
        jt_coord[cnt] = num.toFloat();
        seek_pos = ind + 2;
        ind = jt_pos.indexOf(",", seek_pos);
        cnt++;
    }
    jt_coord[2] += 90;
    ui->widget_Robot->SetRobotRotation(jt_coord, cnt);

}
//------------------------------------------------------------------------------
void TMainWindow::on_comboBox_activated(int index)
{
    RobotMotion->MotionMode =  index+1;
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_x_plus_clicked()
{    
    QString satte;
    int code = RobotMotion->StepMove(1, step, satte);

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
void TMainWindow::on_pushButton_x_minus_clicked()
{
    QString satte;
    int code = RobotMotion->StepMove(1, -step, satte);

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
void TMainWindow::on_pushButton_y_plus_clicked()
{
    QString satte;
    int code = RobotMotion->StepMove(2, step, satte);

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
void TMainWindow::on_pushButton_y_minus_clicked()
{
    QString satte;
    int code = RobotMotion->StepMove(2, -step, satte);

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
void TMainWindow::on_pushButton_z_minus_clicked()
{
    QString satte;
    int code = RobotMotion->StepMove(3, -step, satte);

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
void TMainWindow::on_pushButton_z_plus_clicked()
{
    QString satte;
    int code =  RobotMotion->StepMove(3, step, satte);

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
void TMainWindow::on_pushButton_rx_plus_clicked()
{
    QString satte;
    int code = RobotMotion->StepMove(4, -step, satte);

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
void TMainWindow::on_pushButton_rx_minus_clicked()
{
    QString satte;
    int code = RobotMotion->StepMove(4, step, satte);

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
void TMainWindow::on_pushButton_ry_plus_clicked()
{
    QString satte;
    int code = RobotMotion->StepMove(5, -step, satte);

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
void TMainWindow::on_pushButton_ry_minus_clicked()
{
    QString satte;
    if (RobotMotion->StepMove(5, step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rz_plus_clicked()
{
    QString satte;
    if (RobotMotion->StepMove(6, step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_rz_minus_clicked()
{
    QString satte;
    if (RobotMotion->StepMove(6, -step, satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
}
//------------------------------------------------------------------------------
void TMainWindow::on_spinBox_Step_valueChanged(int arg1)
{
    step = arg1;
}
//------------------------------------------------------------------------------
void TMainWindow::on_pushButton_Move_clicked()
{
    const int len =  RobotMotion->AxisCount;
    float pt[len];
    QString state = "";

    QSpinBox *axisis[MAX_AXIS_COUNT] = {ui->spinBox_X, ui->spinBox_Y,
        ui->spinBox_Z, ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz, ui->spinBox_reserv
    };
    for (int i = 0; i < RobotMotion->AxisCount; i++) {
        pt[i] = axisis[i]->value();
    }

    int code = RobotMotion->MovePoint(pt, state);

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
void TMainWindow::on_pushButton_clicked()
{
    QString satte;
    int code = RobotMotion->DepartMove(ui->doubleSpinBox_Depart->value(), satte);

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
void TMainWindow::on_pushButton_ZERO_clicked()
{
    QString satte;
    if (RobotMotion->SetZero(satte))
        ui->plainTextEdit->appendPlainText(satte);
    else ui->plainTextEdit->appendPlainText("timout error");
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

