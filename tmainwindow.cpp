#include "tmainwindow.h"
#include "ui_tmainwindow.h"
#include "qdebug.h"

TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TMainWindow)
{   
    ui->setupUi(this);

    cPthrd = new TConnectionThread(this, "192.168.0.1");
    cPthrd->Terminate = false;
    cPthrd->start();
}

TMainWindow::~TMainWindow()
{
    cPthrd->Terminate = true;
    cPthrd->terminate();
    delete cPthrd;


    delete ui;
}



void TMainWindow::on_pushButton_x_plus_clicked()
{
    QString cmd = "JT 1 " + QString::number(5);
    cPthrd->ProcessCommand(cmd);
}

void TMainWindow::on_pushButton_x_minus_clicked()
{
    QString cmd = "JT 1 " + QString::number(-5);
    cPthrd->ProcessCommand(cmd);
}

void TMainWindow::on_pushButton_y_plus_clicked()
{
    QString cmd = "JT 2 " + QString::number(5);
    cPthrd->ProcessCommand(cmd);
}

void TMainWindow::on_pushButton_y_minus_clicked()
{
    QString cmd = "JT 2 " + QString::number(-5);
    cPthrd->ProcessCommand(cmd);
}

void TMainWindow::on_pushButton_z_minus_clicked()
{
    QString cmd = "JT 3 " + QString::number(-5);
    cPthrd->ProcessCommand(cmd);
}

void TMainWindow::on_pushButton_z_plus_clicked()
{
    QString cmd = "JT 3 " + QString::number(-5);
    cPthrd->ProcessCommand(cmd);
}
