  #include "tpointdialog.h"
#include "ui_tpointdialog.h"
#include "qdebug.h"

TPointDialog::TPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TPointDialog)
{
    ui->setupUi(this);
}
//------------------------------------------------------------------------------
TPointDialog::~TPointDialog()
{
    delete ui;
}
//------------------------------------------------------------------------------
int TPointDialog::Run(JTPoint *point)
{
    mCoordType = CoordType::JT;
    mCurrentJt = point;

    //высчечиаем оба фрейма
    ui->frame_XYZ->setVisible(true);
    ui->frame_OAT->setVisible(true);

    QSpinBox *axes[6] = {
        ui->spinBox_X, ui->spinBox_Y, ui->spinBox_Z,
        ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz
    };
    for (int i =0; i < 6; i++) {
        float v = (*point)[i];
        qDebug() << "v " <<  v;
        axes[i]->setValue(v);
    }

    return exec();
}
//------------------------------------------------------------------------------
int TPointDialog::Run(DecartPoint *point)
{
    mCoordType = CoordType::XYZOAT;
    mCurrentDecart = point;

    //высчечиаем фрейм XYZ и фрейм угла
    ui->frame_XYZ->setVisible(true);
    ui->frame_OAT->setVisible(true);

    QSpinBox *axes[DecartPoint::CoordCount] = {
        ui->spinBox_X, ui->spinBox_Y, ui->spinBox_Z,
        ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz
    };
    for (int i =0; i < mCurrentDecart->size(); i++) {
        float v = mCurrentDecart->at(i);
        qDebug() << "v " <<  v;
        axes[i]->setValue(v);
    }

    return exec();
}
//------------------------------------------------------------------------------
void TPointDialog::on_pushButton_clicked()
{
    QSpinBox *sp_axisis[6] = {ui->spinBox_X, ui->spinBox_Y,
        ui->spinBox_Z, ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz
    };


    switch (mCoordType)
    {
        case CoordType::JT :
            qDebug() << "ln  " << mCurrentJt->size();
            for (int i = 0; i < mCurrentJt->size(); i++) {
                mCurrentJt->setPoint(i, sp_axisis[i]->value());
                //qDebug() << "i " << i << " " << mCurrentJt[i];
            }
            break;
        case CoordType::XYZOAT :
            for (int i = 0; i < mCurrentDecart->size(); i++) {
                mCurrentDecart->setPoint(i, sp_axisis[i]->value());
            }
            break;
    }
    accept();
}
//------------------------------------------------------------------------------
void TPointDialog::on_pushButton_2_clicked()
{
    reject();
}
