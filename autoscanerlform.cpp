#include "autoscanerlform.h"
#include "ui_autoscanerlform.h"

AutoScanerlForm::AutoScanerlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoScanerlForm)
{
    ui->setupUi(this);
}

AutoScanerlForm::~AutoScanerlForm()
{
    delete ui;
}

void AutoScanerlForm::checkScanAction()
{

}
