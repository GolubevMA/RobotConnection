#include "formremote.h"
#include "tpointdialog.h"
#include "ui_formremote.h"
#include <QtWidgets>
#include "vars.h"
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
    //m_TrackPlanes.clear();
    m_TrackAngles.clear();
    m_TrackJtPoints.clear();
    RobotMotion::loadPoints("point.txt", m_TrackJtPoints);

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

    ui->tableWidget_points->setColumnCount(6);
    UpdateTable();
}
//------------------------------------------------------------------------------
FormRemote::~FormRemote()
{
    RobotMotion::savePoints("point.txt", m_TrackJtPoints);
    updateTimer->stop();
    delete  updateTimer;
    delete ui;  
}
//------------------------------------------------------------------------------
void FormRemote::setObjMotion(RobotMotion *obj)
{
    m_RobotMotion = obj;
    connect(m_RobotMotion, SIGNAL(buildStarted()), this, SLOT(UpdateTrack()), Qt::QueuedConnection);
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
        for (int i = 0; i < JTPoint::PointCount; i++) {
            axisis[i]->setText(QString::number(jt_point[i], 'f', 2));
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
        UpdateTable();
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
        JTPoint pt;
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
    if (MotionMode == 1)
    {
        ui->tableWidget_points->setColumnCount(6);
        ui->tableWidget_points->setHorizontalHeaderItem(0, new QTableWidgetItem("1"));
        ui->tableWidget_points->setHorizontalHeaderItem(1, new QTableWidgetItem("2"));
        ui->tableWidget_points->setHorizontalHeaderItem(2, new QTableWidgetItem("3"));
        ui->tableWidget_points->setHorizontalHeaderItem(3, new QTableWidgetItem("4"));
        ui->tableWidget_points->setHorizontalHeaderItem(4, new QTableWidgetItem("5"));
        ui->tableWidget_points->setHorizontalHeaderItem(5, new QTableWidgetItem("6"));

        //установим чило строк в соответстиве с числом  точек
        int pt_count = m_TrackJtPoints.size();
        ui->tableWidget_points->setRowCount(pt_count );

        for (int d = 0; d < pt_count ; d++)
        {
            //номера точек
            ui->tableWidget_points->setVerticalHeaderItem(d, new QTableWidgetItem(QString::number(d+1)));
            ui->tableWidget_points->setItem(d, 0, new QTableWidgetItem(QString(" %1").arg(m_TrackJtPoints[d][0])));
            ui->tableWidget_points->setItem(d, 1, new QTableWidgetItem(QString(" %1").arg(m_TrackJtPoints[d][1])));
            ui->tableWidget_points->setItem(d, 2, new QTableWidgetItem(QString(" %1").arg(m_TrackJtPoints[d][2])));
            ui->tableWidget_points->setItem(d, 3, new QTableWidgetItem(QString(" %1").arg(m_TrackJtPoints[d][3])));
            ui->tableWidget_points->setItem(d, 4, new QTableWidgetItem(QString(" %1").arg(m_TrackJtPoints[d][4])));
            ui->tableWidget_points->setItem(d, 5, new QTableWidgetItem(QString(" %1").arg(m_TrackJtPoints[d][5])));
        }
    }
    else {
        ui->tableWidget_points->setColumnCount(4);
        ui->tableWidget_points->setHorizontalHeaderItem(0, new QTableWidgetItem("X"));
        ui->tableWidget_points->setHorizontalHeaderItem(1, new QTableWidgetItem("Y"));
        ui->tableWidget_points->setHorizontalHeaderItem(2, new QTableWidgetItem("Z"));
        ui->tableWidget_points->setHorizontalHeaderItem(3, new QTableWidgetItem("A"));
        //ui->tableWidget_points->setHorizontalHeaderItem(4, new QTableWidgetItem("A"));
        //ui->tableWidget_points->setHorizontalHeaderItem(5, new QTableWidgetItem("T"));

        //установим чило строк в соответстиве с числом  точек
        int pt_count = m_TrackPoints.size();
        ui->tableWidget_points->setRowCount(pt_count );

        qDebug() << "ptcount " << pt_count;

        for (int d = 0; d < pt_count ; d++)
        {
            //номера точек
            ui->tableWidget_points->setVerticalHeaderItem(d, new QTableWidgetItem(QString::number(d+1)));
            //координаты точек
            ui->tableWidget_points->setItem(d, 0, new QTableWidgetItem(QString(" %1").arg(m_TrackPoints[d].x())));
            ui->tableWidget_points->setItem(d, 1, new QTableWidgetItem(QString(" %1").arg(m_TrackPoints[d].y())));
            ui->tableWidget_points->setItem(d, 2, new QTableWidgetItem(QString(" %1").arg(m_TrackPoints[d].z())));
            ui->tableWidget_points->setItem(d, 3, new QTableWidgetItem(QString(" %1").arg(m_TrackAngles[d])));
            //ui->tableWidget_points->setItem(d, 4, new QTableWidgetItem(QString(" %1").arg(m_TrackPlanes[d][1])));
            //ui->tableWidget_points->setItem(d, 5, new QTableWidgetItem(QString(" %1").arg(m_TrackPlanes[d][2])));
        }
    }
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_addPt_clicked()
{
    if (MotionMode == 1)
    {
        JTPoint jt;

        TPointDialog dialog(this);
        if (dialog.Run(&jt) == QDialog::Accepted)
        {
            m_TrackJtPoints.insert(ui->tableWidget_points->currentRow()+1,jt);
            //обновляем таблицу
            UpdateTable();
        }
    }
    else {
        QVector3D xyz;
        EulerAngles oat;
        TPointDialog dialog(this);
        if (dialog.Run(&xyz, &oat) == QDialog::Accepted)
        {
            m_TrackPoints.insert(ui->tableWidget_points->currentRow()+1,xyz);
            //m_TrackPlanes.insert(ui->tableWidget_points->currentRow()+1,oat);
            //послыаем сиганл о перерикое
            emit UpdateTargetPoints(m_TrackPoints);
            //обновляем таблицу
            UpdateTable();
        }
    }
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_RemovePt_clicked()
{
    if (MotionMode == 1) {
        m_TrackJtPoints.removeAt(ui->tableWidget_points->currentRow());
    }
    else  {
        m_TrackPoints.removeAt(ui->tableWidget_points->currentRow());
        //m_TrackPlanes.removeAt(ui->tableWidget_points->currentRow());
        //послыаем сиганл о перерикое
        emit UpdateTargetPoints(m_TrackPoints);
    }
    //обновляем таблицу
    UpdateTable();
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_ChangePt_clicked()
{
    int ind = ui->tableWidget_points->currentRow();
    if (MotionMode == 1)
    {
        JTPoint curr_pt = m_TrackJtPoints.at(ind);
        TPointDialog dialog(this);
        if (dialog.Run(&curr_pt) == QDialog::Accepted)
        {
            qDebug() << "replace " << ind;
            m_TrackJtPoints.replace(ind, curr_pt);
            //послыаем сиганл о перерикое
            //emit UpdateTargetPoints(m_TrackPoints);
            //обновляем таблицу
            qDebug() << " updd ";
            UpdateTable();
        }
    }
    else {
        QVector3D curr_pt = m_TrackPoints.at(ind);
        float curr_angl = m_TrackAngles.at(ind);
        //EulerAngles curr_oat = m_TrackPlanes.at(ind);
        TPointDialog dialog(this);
        if (dialog.Run(&curr_pt, &curr_angl) == QDialog::Accepted)
        {
            m_TrackPoints.replace(ind, curr_pt);
            //послыаем сиганл о перерикое
            emit UpdateTargetPoints(m_TrackPoints);
            //обновляем таблицу
            UpdateTable();
        }
    }
}
//------------------------------------------------------------------------------
//void FormRemote::on_tableWidget_points_cellClicked(int row, int column)
//{

//}
//------------------------------------------------------------------------------
//запускаем программу посторения траектории
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_BuildStart_clicked()
{
    m_RobotMotion->StartBuild(ui->spinBox_Speed->value());
}
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_BuildStop_clicked()
{
    m_RobotMotion->StopBuild();
}
//------------------------------------------------------------------------------
void FormRemote::UpdateTrack()
{
    qDebug() << "parsee";
    m_RobotMotion->ParseTrack(m_TrackJtPoints, ui->spinBox_Speed->value());
}
//------------------------------------------------------------------------------
//движеие по окружности
//------------------------------------------------------------------------------
void FormRemote::on_pushButton_MoveArc_clicked()
{
    //форимруем токи окружности
    QList<QVector3D> arcpts = {QVector3D(0,0,-50), QVector3D(0,50,50), QVector3D(0, 50, -50)};
    m_RobotMotion->LinearMove(arcpts, ui->spinBox_Speed->value(), 100);
}
//------------------------------------------------------------------------------

