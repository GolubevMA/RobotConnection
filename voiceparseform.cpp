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
//инициализируем команды
//------------------------------------------------------------------------------
void VoiceParseForm::initCmdDictionary()
{
    //запкск распозанвания
    m_VoiceManageStartCmd = {QString("джарвис")};
    //остнвока распознавания
    m_VoiceManageEndCmd = {QString("спасибо"), QString("счастливо"), QString("достаточно"), QString("стоп"), QString("пока")};
    //приветвтсеие
    m_GreetingsCmd = {QString("привет"), QString("поздоровайся"), QString("доброе утро"), QString("здарвствуй")};
}
//------------------------------------------------------------------------------
//разбираем полученную команду
//------------------------------------------------------------------------------
void VoiceParseForm::totalResult(QString res)
{

    QSet<QString> inData = res.toLower().split(" ").toSet();
    //проверяем наличие активаотора команды запуска распозанвания
    if (!m_VoiceManage && inData.intersects(m_VoiceManageStartCmd))
    {
        //запускаемм управление голосом
        m_VoiceManage = true;
        speak(QString("Я к вашим услугам"));
        qDebug() << "startPArse!";
    }
    else {
        //основкак управления голосом
        if (!m_VoiceManage && inData.intersects(m_VoiceManageStartCmd)) {
            m_VoiceManage = false;
            speak("Заканчиваю сеанс");
        }
        else if  (inData.intersects(m_GreetingsCmd)) {
            //выполенм команду привтевия
            QList<JTPoint> pts;
            const std::array<float, 6> ptf1 = {0,0,-90,0,0,0};
            JTPoint pt1(ptf1);
            const std::array<float, 6> ptf2 = {0,0-60,-70,30,0,0};
            JTPoint pt2(ptf2);
            pts.append(pt1); pts.append(pt2);
            m_RobotMotion->ParseTrackJT(pts, 30);
            speak("Приветвтие");
        }
    }

}
//------------------------------------------------------------------------------
void VoiceParseForm::UpdateSystemState()
{
    ui->label_Status->setText("Распознано" + m_RespText);
    if (m_VoiceParser->isActive()) {
        ui->pushButton_Recognize->setIcon(m_NewPartRec ?  *m_SpeakIcon :  *m_OnIcon);
    }
    else  ui->pushButton_Recognize->setIcon(*m_OffIcon);
}
//------------------------------------------------------------------------------
//генериуем свук соотвветвутющий преданнму тексту
//------------------------------------------------------------------------------
void VoiceParseForm::speak(QString text)
{
    ui->label_ResponseInfo->setText("Выполняется Команда " + text);
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
    }
    else if (!m_NewPartRec) {
        m_NewPartRec = true;        
    }
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
void VoiceParseForm::on_pushButton_Recognize_2_clicked()
{
    QString s1("Джарвис");
    QString s2("Шарвис");
    qDebug() <<  m_VoiceParser->compareString(s1, s2);
}
