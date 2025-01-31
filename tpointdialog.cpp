#include "tpointdialog.h"
#include "ui_tpointdialog.h"
#include "qdebug.h"

TPointDialog::TPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TPointDialog)
{
    ui->setupUi(this);
}

TPointDialog::~TPointDialog()
{
    delete ui;
}

int TPointDialog::Run(QList<float> *axises, const int MaxAxisCount)
{
    AxisesValues = axises;

    QSpinBox *sp_axisis[MaxAxisCount] = {ui->spinBox_X, ui->spinBox_Y,
        ui->spinBox_Z, ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz, ui->spinBox_reserv
    };

    for (int i = 0; i < AxisesValues->length(); i++)
    {
        sp_axisis[i]->setValue(AxisesValues->at(i));
    }

    for (int i = 6; i < MaxAxisCount;  i++) {
        sp_axisis[i]->setVisible(false);
    }

    return exec();
}


void TPointDialog::on_pushButton_clicked()
{
    QSpinBox *sp_axisis[7] = {ui->spinBox_X, ui->spinBox_Y,
        ui->spinBox_Z, ui->spinBox_rx, ui->spinBox_ry, ui->spinBox_rz, ui->spinBox_reserv
    };

    for (int i = 0; i < AxisesValues->length(); i++) {
        AxisesValues->replace(i, sp_axisis[i]->value());
        qDebug() << "i " << i << " " << AxisesValues->at(i);
    }

    accept();
}

void TPointDialog::on_pushButton_2_clicked()
{
    reject();
}
