#ifndef AUTOSCANERLFORM_H
#define AUTOSCANERLFORM_H

#include <QWidget>
#include <QVector3D>
#include "kawasakimotion.h"
#include <QCloseEvent>
#include <QShowEvent>
#include "autoscancontroller.h"

//класс инкаписулируший автоматическое управление сканированием обьекта по модели обьекта

namespace Ui {
class AutoScanerlForm;
}

class AutoScanerlForm : public QWidget
{
    Q_OBJECT

public:
    explicit AutoScanerlForm(QWidget *parent = nullptr);
    ~AutoScanerlForm();

    void setControlller(AutoScanController *obj);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_Check_clicked();

    void on_pushButton_2_clicked();

public slots :
    void updateScanParams(bool scan_flag, int scan_state);

private:
    Ui::AutoScanerlForm *ui;


    //обьект управления  сканирвоанием
    AutoScanController *m_ScanController;
    //флаг проверки пармаетров сканирования
    bool mCorrectParams;
    //проверка точек траектороии

    //void checkTargetPoints();
    void checkConfiguration();

};

#endif // AUTOSCANERLFORM_H
