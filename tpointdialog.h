#ifndef TPOINTDIALOG_H
#define TPOINTDIALOG_H

#include <QDialog>
#include "robotmotion.h"

namespace Ui {
class TPointDialog;
}

class TPointDialog : public QDialog
{
    Q_OBJECT

public:

    explicit TPointDialog(QWidget *parent = 0);
    ~TPointDialog();

    int Run(JTPoint *point);
    int Run(QVector3D *xyz, EulerAngles *oat);
    int Run(QVector3D *xyz);
    int Run(QVector3D *xyz, float *angle);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:

    enum CoordType {JT, XYZOAT, XYZ,XYZA};

    //тип координаты
    int mCoordType = CoordType::JT;

    //текущеие коорлинаты
    JTPoint *mCurrentJt;
    QVector3D *mCurrentXYZ;
    QVector3D *mCurrentOAT;
    float *mCurrentAngle;

    Ui::TPointDialog *ui;
};

#endif // TPOINTDIALOG_H
