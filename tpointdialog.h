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
    int Run(DecartPoint *point);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:

    enum CoordType {JT, XYZOAT};

    //тип координаты
    int mCoordType = CoordType::JT;

    //текущеие коорлинаты
    JTPoint *mCurrentJt;
    DecartPoint *mCurrentDecart;

    Ui::TPointDialog *ui;
};

#endif // TPOINTDIALOG_H
