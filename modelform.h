#ifndef MODELFORM_H
#define MODELFORM_H

#include <QWidget>
#include <QVector3D>

namespace Ui {
class ModelForm;
}

class ModelForm : public QWidget
{
    Q_OBJECT

public:
    explicit ModelForm(QWidget *parent = nullptr);
    ~ModelForm();

    void createModel();
    void updateState();

private slots:
    void on_spinBoxEndX_valueChanged(double arg1);

    void on_spinBoxEndY_valueChanged(double arg1);

    void on_spinBoxEndZ_valueChanged(double arg1);

    void on_spinBoxStartX_valueChanged(double arg1);

    void on_spinBoxStartY_valueChanged(double arg1);

    void on_spinBoxStartZ_valueChanged(double arg1);

    void on_spinBoxRad_valueChanged(double arg1);

    void on_spinBoxAngle_valueChanged(double arg1);

    void on_pushButton_clicked();

private:

    bool mUpdateVars = false;

    Ui::ModelForm *ui;
};

#endif // MODELFORM_H
