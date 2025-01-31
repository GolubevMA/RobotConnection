#ifndef TPOINTDIALOG_H
#define TPOINTDIALOG_H

#include <QDialog>

namespace Ui {
class TPointDialog;
}

class TPointDialog : public QDialog
{
    Q_OBJECT

public:

    QList<float> *AxisesValues;

    explicit TPointDialog(QWidget *parent = 0);
    ~TPointDialog();

    int Run(QList<float> *axises, const int maxax);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TPointDialog *ui;
};

#endif // TPOINTDIALOG_H
