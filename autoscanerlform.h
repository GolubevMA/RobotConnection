#ifndef AUTOSCANERLFORM_H
#define AUTOSCANERLFORM_H

#include <QWidget>

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

public slots :

    //слот контролирущий процесс сканирвоания
    void checkScanAction();

private:
    Ui::AutoScanerlForm *ui;

    //здеьс булет хранится модель сканирвоания
};

#endif // AUTOSCANERLFORM_H
