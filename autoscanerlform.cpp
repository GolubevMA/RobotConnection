#include "autoscanerlform.h"
#include "ui_autoscanerlform.h"
#include "qdebug.h"
#include "decartpoint.h"
#include <QSettings>
#include "QMessageBox"
//------------------------------------------------------------------------------
AutoScanerlForm::AutoScanerlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoScanerlForm)
//------------------------------------------------------------------------------
{    
    mCorrectParams = false;
    m_ScanController = NULL;

    ui->setupUi(this);
}
//------------------------------------------------------------------------------
AutoScanerlForm::~AutoScanerlForm()
{
    delete ui;
}
//------------------------------------------------------------------------------
//устновим обьект упрпвления
//------------------------------------------------------------------------------
void AutoScanerlForm::setControlller(AutoScanController *obj)
{
     m_ScanController= obj;
     connect(m_ScanController, SIGNAL(scanState(bool,int)), this, SLOT(updateScanParams(bool,int)));
}
//------------------------------------------------------------------------------
void AutoScanerlForm::updateScanParams(bool scan_flag, int scan_state)
{
    QString msg = scan_flag ? tr("ScanStated") : tr("ScanStopped");
    ui->label_ScanInfo->setText(msg +  " state " + QString::number(scan_state));
}
//------------------------------------------------------------------------------
//обновлем параметры дуги и проверям начальуню точку
//------------------------------------------------------------------------------
void AutoScanerlForm::checkConfiguration()
{
    //устанвим парматры сканрования
    QList<DecartPoint> lpt = SelectedModel->getTarckList();
    m_ScanController->setScanParams(lpt, SelectedModel->getStartPoint(), ui->spinBoxSpeed->value(),ui->spinBoxLines->value());
    QMessageBox::information(this, "ScanForm", tr("Model loaded!"));
    mCorrectParams = true;

//    int res = m_KinTaskSolv.solveOZK(pt, jpt);
//    if (res) {
//        QMessageBox::information(this, "Check prams", "Params correct");
//    }
//    else QMessageBox::critical(this, "Check prams", "Point ureacheble " + QString::number(res));
}
//------------------------------------------------------------------------------
//запуск сканирвоания образца
//------------------------------------------------------------------------------
void AutoScanerlForm::on_pushButton_clicked()
{
    checkConfiguration();
    if ((!mCorrectParams) || (m_ScanController->startScan() < 0))
    {
        QMessageBox::critical(this, "Check prams", "No Model Loaded");
    }
}
//---------------------------------------------------------------------------
void AutoScanerlForm::on_pushButton_Check_clicked()
{
    checkConfiguration();
}
//---------------------------------------------------------------------------
void AutoScanerlForm::on_pushButton_2_clicked()
{
   m_ScanController->stopScan();
}
