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

//    QSpinBox *axes[6] = {
//        ui->spinBox_X, ui->spinBox_Y, ui->spinBox_Z,
//        ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_ry
//    };

//    for (int i =0; i < 6; i++) {
//        axes[i]->setValue(point->at(i));
//    }

    return exec();
}
//------------------------------------------------------------------------------
int TPointDialog::Run(QVector3D *xyz, EulerAngles *oat)
{
    mCoordType = CoordType::XYZOAT;
    mCurrentXYZ = xyz;
    mCurrentOAT = oat;

    //высчечиаем оба фрейма
    ui->frame_XYZ->setVisible(true);
    ui->frame_OAT->setVisible(true);

    ui->spinBox_X->setValue(xyz->x());
    ui->spinBox_Y->setValue(xyz->y());
    ui->spinBox_Z->setValue(xyz->z());

    ui->spinBox_rx->setValue(oat->x());
    ui->spinBox_ry->setValue(oat->y());
    ui->spinBox_rz->setValue(oat->z());

    return exec();
}
//------------------------------------------------------------------------------
int TPointDialog::Run(QVector3D *xyz)
{
    mCoordType = CoordType::XYZ;
    mCurrentXYZ = xyz;

    //высчечиаем фрейм XYZ
    ui->frame_XYZ->setVisible(true);
    ui->frame_OAT->setVisible(false);

    ui->spinBox_X->setValue(xyz->x());
    ui->spinBox_Y->setValue(xyz->y());
    ui->spinBox_Z->setValue(xyz->z());

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
            for (int i = 0; i < mCurrentJt->length(); i++) {
                mCurrentJt->replace(i, sp_axisis[i]->value());
                qDebug() << "i " << i << " " << mCurrentJt->at(i);
            }
            break;
        case CoordType::XYZOAT :
            mCurrentXYZ->setX(sp_axisis[0]->value());
            mCurrentXYZ->setY(sp_axisis[1]->value());
            mCurrentXYZ->setZ(sp_axisis[2]->value());

            mCurrentOAT->setX(sp_axisis[3]->value());
            mCurrentOAT->setY(sp_axisis[4]->value());
            mCurrentOAT->setZ(sp_axisis[5]->value());
            break;

        case CoordType::XYZ :
            mCurrentXYZ->setX(sp_axisis[0]->value());
            mCurrentXYZ->setY(sp_axisis[1]->value());
            mCurrentXYZ->setZ(sp_axisis[2]->value());
            break;
    }
    accept();
}
//------------------------------------------------------------------------------
void TPointDialog::on_pushButton_2_clicked()
{
    reject();
}
