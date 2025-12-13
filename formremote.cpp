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
    CurrentPoint = 0;

    ui->setupUi(this);

    QLabel *axisis[MAX_AXIS_COUNT] = {ui->label_axis1, ui->label_axis2,
        ui->label_axis3, ui->label_axis4, ui->label_axis5, ui->label_axis6, ui->label_axis7
    };

    for (int i = 6; i < MAX_AXIS_COUNT;  i++) {
        axisis[i]->setVisible(false);
    }

    updateTimer = new QTimer();
    updateTimer->start(16);

    m_TrackPoints.clear();

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

    connect(ui->tableWidget_points, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(on_pushButton_ChangePt_clicked()));


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
            axisis[i]->setText(QString::number(jt_point.at(i), 'f', 2));
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
        m_RobotMotion->StepMoveJT(axis, step, ui->spinBox_Speed->value());
    }
    else if (MotionMode == 2) {
        m_RobotMotion->StepMoveXYZ(axis, step, ui->spinBox_Speed->value());
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
        m_RobotMotion->StepMoveJT(axis, -step, ui->spinBox_Speed->value());
    }
    else if (MotionMode == 2) {
        m_RobotMotion->StepMoveXYZ(axis, -step, ui->spinBox_Speed->value());
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
    if (MotionMode == 1)
    {
        JTPoint pt = {0,0,0,0,0,0}; //m_RobotMotion->GetCurrentJT();


        TPointDialog dialog(this);
        if (dialog.Run(&pt) == QDialog::Accepted)
            m_RobotMotion->MovePointJT(pt, ui->spinBox_Speed->value());
    }
    else
    {
        QVector3D xyz;
        EulerAngles oat;
        TPointDialog dialog(this);
        if (dialog.Run(&xyz, &oat) == QDialog::Accepted)
            m_RobotMotion->MovePointXYZ(xyz, oat, ui->spinBox_Speed->value());
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
//активация/деактивация режима движения по траектории
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_linear_clicked(bool checked)
{
    ui->frame_Trac->setVisible(checked);
}
//------------------------------------------------------------------------------
//обновим таблицу точек
//------------------------------------------------------------------------------
void FormRemote::UpdateTable()
{
    //очистим таблицу
    ui->tableWidget_points->clear();

    //формируем столбцы
    ui->tableWidget_points->setHorizontalHeaderItem(0, new QTableWidgetItem("X"));
    ui->tableWidget_points->setHorizontalHeaderItem(1, new QTableWidgetItem("Y"));
    ui->tableWidget_points->setHorizontalHeaderItem(2, new QTableWidgetItem("Z"));

    //установим чило строк в соответстиве с числом  точек
    int pt_count = m_TrackPoints.size();
    ui->tableWidget_points->setRowCount(pt_count );

    for (int d = 0; d < pt_count ; d++)
    {
        //номера точек
        ui->tableWidget_points->setVerticalHeaderItem(d, new QTableWidgetItem(QString::number(d+1)));
        ui->tableWidget_points->setItem(d, 0, new QTableWidgetItem(QString(" %1").arg(m_TrackPoints[d].x())));
        ui->tableWidget_points->setItem(d, 1, new QTableWidgetItem(QString(" %1").arg(m_TrackPoints[d].y())));
        ui->tableWidget_points->setItem(d, 2, new QTableWidgetItem(QString(" %1").arg(m_TrackPoints[d].z())));
    }
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_addPt_clicked()
{
    QVector3D xyz;
    TPointDialog dialog(this);
    if (dialog.Run(&xyz) == QDialog::Accepted)
    {
        m_TrackPoints.insert(ui->tableWidget_points->currentRow()+1,xyz);
        //послыаем сиганл о перерикое
        emit UpdateTargetPoints(m_TrackPoints);
        //обновляем таблицу
        UpdateTable();
    }
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_RemovePt_clicked()
{
    m_TrackPoints.removeAt(ui->tableWidget_points->currentRow());
    //послыаем сиганл о перерикое
    emit UpdateTargetPoints(m_TrackPoints);
    //обновляем таблицу
    UpdateTable();
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_ChangePt_clicked()
{
    int ind = ui->tableWidget_points->currentRow();
    QVector3D curr_pt = m_TrackPoints.at(ind);
    TPointDialog dialog(this);
    if (dialog.Run(&curr_pt) == QDialog::Accepted)
    {
        m_TrackPoints.replace(ind, curr_pt);
        //послыаем сиганл о перерикое
        emit UpdateTargetPoints(m_TrackPoints);
        //обновляем таблицу
        UpdateTable();
    }
}
//------------------------------------------------------------------------------
//void FormRemote::on_tableWidget_points_cellClicked(int row, int column)
//{

//}
//------------------------------------------------------------------------------
//запуск движения по траектории
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_LinearMove_clicked()
{
    //RobotMotion->MotionMode = TRobotMotionThread::MotioType::BASE;
    m_RobotMotion->LinearMove(m_TrackPoints, ui->spinBox_Speed->value(),0);
}
//------------------------------------------------------------------------------
//движеие по окружности
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_MoveArc_clicked()
{
    //форимруем токи окружности
    QList<QVector3D> arcpts = {QVector3D(0,0,0), QVector3D(50,0,50), QVector3D(100, 0, 0)};
    m_RobotMotion->LinearMove(arcpts, ui->spinBox_Speed->value(), 100);
}
//------------------------------------------------------------------------------
