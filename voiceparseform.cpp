#include "voiceparseform.h"
#include "ui_voiceparseform.h"
#include <QMessageBox>
//------------------------------------------------------------------------------
VoiceParseForm::VoiceParseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoiceParseForm)
{
    m_RobotMotion = NULL;
    //инициазируем обьект расопзванчения
    m_VoiceParser = new VoiceResponser;
    m_NewPartRec = false;

    m_OffIcon  = new QIcon(":/img/micro_off.png");
    m_OnIcon = new QIcon(":/img/micro.png");
    m_SpeakIcon = new QIcon(":/img/micro_req.png");

    connect(m_VoiceParser, SIGNAL(partial_result(QString)), this, SLOT(partialResult(QString)));
    connect(m_VoiceParser, SIGNAL(total_result(QString)), this, SLOT(totalResult(QString)));
    connect(m_VoiceParser, SIGNAL(UpdateState(int)), this, SLOT(updateState(int)));

    ui->setupUi(this);

    ui->label_Status->setText("Распознавание отключено");
    ui->pushButton_Recognize->setIcon(*m_OffIcon);
}
//------------------------------------------------------------------------------
VoiceParseForm::~VoiceParseForm()
{
    delete ui;   
    delete m_OffIcon;
    delete m_OnIcon;
    delete m_SpeakIcon;

    delete m_VoiceParser;
}
//------------------------------------------------------------------------------
void VoiceParseForm::setRobotObject(RobotMotion *obj)
{
    m_RobotMotion = obj;
}
//------------------------------------------------------------------------------
//запускаем обпработку
//------------------------------------------------------------------------------
void VoiceParseForm::on_pushButton_Recognize_clicked()
{
    if (!m_VoiceParser->isActive()) {
        m_VoiceParser->startRecognize();
    }
    else {
        m_VoiceParser->stopRecognize();
    }
}
//------------------------------------------------------------------------------
void VoiceParseForm::partialResult(QString res)
{
    ui->plainTextEdit_Message->appendPlainText(res);

    if (res.isEmpty()) {
        m_NewPartRec = false;
        ui->pushButton_Recognize->setIcon(*m_OnIcon);
    }
    else if (!m_NewPartRec) {
        m_NewPartRec = true;
        ui->pushButton_Recognize->setIcon(*m_SpeakIcon);
    }


    ui->pushButton_Recognize->setIcon(*m_OnIcon);
}
//------------------------------------------------------------------------------
void VoiceParseForm::totalResult(QString res)
{
    ui->label_ResponseInfo->setText("Распознано" + res);
    m_NewPartRec = false;
    ui->pushButton_Recognize->setIcon(*m_OnIcon);
}
//------------------------------------------------------------------------------
void VoiceParseForm::updateState(int st)
{
    if (st > 0) {
        ui->pushButton_Recognize->setIcon(*m_OnIcon);
        ui->label_Status->setText("Распознавание включено");
    }
    else  {
        ui->pushButton_Recognize->setIcon(*m_OffIcon);
        ui->label_Status->setText("Распознавание отключено");
    }
}
//------------------------------------------------------------------------------
