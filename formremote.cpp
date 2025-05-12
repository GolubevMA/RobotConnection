#include "formremote.h"
#include "tpointdialog.h"
#include "ui_formremote.h"
#include <QtWidgets>
//------------------------------------------------------------------------------
const int MAX_AXIS_COUNT = 7;
//------------------------------------------------------------------------------
FormRemote::FormRemote(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRemote)
{
    step = 5;
    MotionMode = 1;
    m_RobotMotion = NULL;
    UpdateVarsFlag = false;

    ui->setupUi(this);

    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    for (int i = 6; i < MAX_AXIS_COUNT;  i++) {
        axisis[i]->setVisible(false);
    }

    updateTimer = new QTimer();
    updateTimer->start(16);

    connect(ui->pushButton_x_plus, SIGNAL(clicked()), this, SLOT(step_plus_clicked()));
    connect(ui->pushButton_y_plus, SIGNAL(clicked()), this, SLOT(step_plus_clicked()));
    connect(ui->pushButton_z_plus, SIGNAL(clicked()), this, SLOT(step_plus_clicked()));
    connect(ui->pushButton_rx_plus, SIGNAL(clicked()), this, SLOT(step_plus_clicked()));
    connect(ui->pushButton_ry_plus, SIGNAL(clicked()), this, SLOT(step_plus_clicked()));
    connect(ui->pushButton_rz_plus, SIGNAL(clicked()), this, SLOT(step_plus_clicked()));

    connect(ui->pushButton_x_minus, SIGNAL(clicked()), this, SLOT(step_minus_clicked()));
    connect(ui->pushButton_y_minus, SIGNAL(clicked()), this, SLOT(step_minus_clicked()));
    connect(ui->pushButton_z_minus, SIGNAL(clicked()), this, SLOT(step_minus_clicked()));
    connect(ui->pushButton_rx_minus, SIGNAL(clicked()), this, SLOT(step_minus_clicked()));
    connect(ui->pushButton_ry_minus, SIGNAL(clicked()), this, SLOT(step_minus_clicked()));
    connect(ui->pushButton_rz_minus, SIGNAL(clicked()), this, SLOT(step_minus_clicked()));

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(UpdateSystemState()));
}
//------------------------------------------------------------------------------
FormRemote::~FormRemote()
{
    updateTimer->stop();
    delete  updateTimer;
    delete ui;
}
//------------------------------------------------------------------------------
void FormRemote::setObjMotion(RobotMotion *obj)
{
    m_RobotMotion = obj;
}
//------------------------------------------------------------------------------
void FormRemote::showEvent(QShowEvent  *event)
{

    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    //грузим значения праматров ui
    QSettings sett(QApplication::organizationName(), QApplication::applicationName());

    sett.beginGroup("MainForm");
    int spin_count = sett.value("spin_box_cnt", MAX_AXIS_COUNT).toInt();
    for (int i = 0; i < spin_count; i++) {
        axisis[i]->setText(sett.value(QString("spin_box_%1").arg(i), 10).toString());
    }
    ui->spinBox_Step->setValue(sett.value("step",10).toFloat());
    sett.endGroup();

}
//------------------------------------------------------------------------------
void FormRemote::closeEvent(QCloseEvent *event)
{
    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    //грузим значения праматров ui
    QSettings sett(QApplication::organizationName(), QApplication::applicationName());
    sett.beginGroup("MainForm");

    sett.setValue("spin_box_cnt",MAX_AXIS_COUNT);
    for (int i = 0; i < MAX_AXIS_COUNT; i++) {
        sett.setValue(QString("spin_box_%1").arg(i), axisis[i]->text().toFloat());
    }
    sett.setValue("step",ui->spinBox_Step->value());
    sett.endGroup();
}
//------------------------------------------------------------------------------
//обновляем состояние графичексого интерфейса в соотвевсие с состоянием робота
//------------------------------------------------------------------------------
void FormRemote::UpdateSystemState()
{
    if (m_RobotMotion == NULL) return;

    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    UpdateVarsFlag = true;

    ui->comboBox->setCurrentIndex(MotionMode - 1);
    if (MotionMode == 1)
    {
        JTPoint jt_point = m_RobotMotion->GetCurrentJT();
        for (int i = 0; i < m_RobotMotion->MaxAxisCount; i++) {
            //qDebug() << " ax " << i << " v " << jt_point.at(i);
            axisis[i]->setText(QString::number(jt_point.at(i)));
        }
    }
    else {
        QVector3D xyz_point = m_RobotMotion->GetCurrentXYZ();
        for (int i = 0; i < 3; i++)
        {
            axisis[i]->setText(QString::number(xyz_point[i]));
        }
        EulerAngles oat_point = m_RobotMotion->GetCurrentOAT();
        for (int i = 0; i < 3; i++)
        {
            axisis[i+3]->setText(QString::number(oat_point[i]));
        }
    }
    //ui->label_freq->setText(QString::number(RobotMotion->MotionFreq));
    UpdateVarsFlag = false;

}
//------------------------------------------------------------------------------
void FormRemote::on_spinBox_Step_valueChanged(int arg1)
{
    step = arg1;
}
//------------------------------------------------------------------------------
void FormRemote::on_comboBox_activated(int index)
{
    if (!UpdateVarsFlag)
    {
        MotionMode =  index+1;
        UpdateSystemState();
    }
}
//------------------------------------------------------------------------------
//прещение на шаг
//------------------------------------------------------------------------------
void FormRemote::step_plus_clicked()
{
    //кнопак излучившая сигнал
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if (btn == NULL) return;

    QPushButton *btns[MAX_AXIS_COUNT-1] = {ui->pushButton_x_plus, ui->pushButton_y_plus, ui->pushButton_z_plus,
        ui->pushButton_rx_plus, ui->pushButton_ry_plus, ui->pushButton_rz_plus};

    int axis = -1;
    for (int i =0; i < MAX_AXIS_COUNT-1; i++) {
        if (btns[i] == btn) {
            axis = i+1;
            break;
        }
    }
    if (axis < 0) return;

    if (MotionMode == 1) {
        m_RobotMotion->StepMoveJT(axis, step);
    }
    else if (MotionMode == 2) {
        m_RobotMotion->StepMoveXYZ(axis, step);
    }
}
//------------------------------------------------------------------------------
void FormRemote::step_minus_clicked()
{
    //кнопак излучившая сигнал
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if (btn == NULL) return;

    QPushButton *btns[MAX_AXIS_COUNT-1] = {ui->pushButton_x_minus, ui->pushButton_y_minus, ui->pushButton_z_minus,
        ui->pushButton_rx_minus, ui->pushButton_ry_minus, ui->pushButton_rz_minus};

    int axis = -1;
    for (int i =0; i < MAX_AXIS_COUNT-1; i++) {
        if (btns[i] == btn) {
            axis = i+1;
            break;
        }
    }
    if (axis < 0) return;

    if (MotionMode == 1) {
        m_RobotMotion->StepMoveJT(axis, -step);
    }
    else if (MotionMode == 2) {
        m_RobotMotion->StepMoveXYZ(axis, -step);
    }
}
//------------------------------------------------------------------------------
//удержание  движения
//------------------------------------------------------------------------------
//void FormRemote::hold_move()
//{
//}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_Move_clicked()
{
    QList<float> pt;
    TPointDialog dialog(this);
    if (dialog.Run(&pt, RobotMotion::MaxAxisCount) == QDialog::Accepted)
    {        
        if (MotionMode == 1) {
            m_RobotMotion->MovePointJT(pt);
        }
        else if (MotionMode == 2) {
            QVector3D xyz = QVector3D(pt[0], pt[1], pt[2]);
            EulerAngles oat = EulerAngles(pt[3], pt[4], pt[5]);
            m_RobotMotion->MovePointXYZ(xyz, oat);
        }
    }
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_clicked()
{
    QString satte;
    //cherResonse(RobotMotion->DepartMove(ui->doubleSpinBox_Depart->value(), satte));
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_ZERO_clicked()
{
    m_RobotMotion->SetZero();
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_linear_clicked()
{
    //RobotMotion->MotionMode = TRobotMotionThread::MotioType::BASE;
    UpdateSystemState();
    QString satte;


//    TPoint p1 = m_RobotMotion->coord_xyz;
//    TPoint p2 = p1;
//    p2[0] += 50;
//    TPoint p3 = p2;
//    p3[2] += 50;


//    QList<TPoint> ppt  = {p1,p2,p3};

//    cherResonse(RobotMotion->LinearMove(ppt));
}

