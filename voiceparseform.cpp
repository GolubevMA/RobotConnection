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
    m_VoiceManage = false;

    m_OffIcon  = new QIcon(":/img/micro_off.png");
    m_OnIcon = new QIcon(":/img/micro.png");
    m_SpeakIcon = new QIcon(":/img/micro_req.png");

    //инициализируем словри команд
    initCmdDictionary();

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
    //вращение
    m_RotateCmd = {QString("повернуть"), QString("поверни"), QString("перемести")};
    //look
    m_LookCmd = {QString("посмтори"), QString("на меня"), QString("посмотри"), QString("смотри")};
}
//------------------------------------------------------------------------------
//проверяет налчиие схожих строк в набоах s1 s2 производя неточное сравнение строк
//------------------------------------------------------------------------------
double VoiceParseForm::intersectsJaro(QList<QString> &s1, QList<QString> &s2)
{
    qDebug() << "ceckInterrSect ";
    QVector<double> interSecVector;
    foreach (QString str, s1) {
        foreach (QString str_c, s2) {
            double koff = VoiceResponser::compareString(str, str_c);
            qDebug() << "interset " << str << " 2 " << str_c << " k " << koff;
            interSecVector.append(koff);
        }
    }
    if (interSecVector.empty()) return  0;

    double max = interSecVector[0];
    for (int i =0; i < interSecVector.size(); i++) {
        if (interSecVector[i] > max) max = interSecVector[i];
    }
    return max;
}
//------------------------------------------------------------------------------
//разбираем полученную команду
//------------------------------------------------------------------------------
void VoiceParseForm::totalResult(QString res)
{
    m_RespText = res;
    QList<QString> inData = res.toLower().split(" ");
    //проверяем наличие активаотора команды запуска распозанвания
    //if (!m_VoiceManage && inData.intersects(m_VoiceManageStartCmd))
    if (!m_VoiceManage)
    {
        if (intersectsJaro(inData, m_VoiceManageStartCmd) > 0.7)
        {
            //запускаемм управление голосом
            m_VoiceManage = true;
            speak(QString("Я к вашим услугам"));
            qDebug() << "startPArse!";
        }
    }
    else
    {
        //обработка глолсовых команд
        enum Commands {Greetings = 1, Rotate, LookAtMe, StopParse};
        //слоаврь команд и
        QMap<int, double> cmd_map;
        cmd_map.insert(Greetings, intersectsJaro(inData, m_GreetingsCmd));
        cmd_map.insert(Rotate, intersectsJaro(inData, m_RotateCmd));
        cmd_map.insert(LookAtMe, intersectsJaro(inData, m_LookCmd));
        cmd_map.insert(StopParse, intersectsJaro(inData, m_VoiceManageEndCmd));

        double max = 0; int max_key = 0;
        for (auto it = cmd_map.cbegin(); it != cmd_map.cend(); ++it) {
            if (it.value() > max) {
                max = it.value();
                max_key = it.key();
                qDebug() << "key " << max_key << " avl "<< max;
            }
        }
        //оюраюотаем команду с масимлаьным сходстовм строки
        if (max > 0.7)
        {
            switch (max_key)
            {
            case Greetings :
                {
                    //выполенм команду привтевия
                    QList<JTPoint> pts;
                    const std::array<float, 6> ptf1 = {0,0,-90,0,0,0};
                    JTPoint pt1(ptf1);
                    const std::array<float, 6> ptf2 = {0,0,-45,0,0,0};
                    JTPoint pt2(ptf2);
                    const std::array<float, 6> ptf3 = {0,0,-120,0,0,0};
                    JTPoint pt3(ptf3);
                    const std::array<float, 6> ptf4 = {0,0,-90,0,0,0};
                    JTPoint pt4(ptf4);
                    pts.append(pt1); pts.append(pt2); pts.append(pt3); pts.append(pt4);
                    speak("Приветвтие");
                    m_RobotMotion->ParseTrackJT(pts, 30);
                }
                break;
            case LookAtMe :
                {
                    QList<JTPoint> pts;
                    const std::array<float, 6> ptf1 = {120,0,90,0,15,0};
                    JTPoint pt1(ptf1);
                    speak("YНа меня");
                    pts.append(pt1);
                    m_RobotMotion->ParseTrackJT(pts, 40);
                }
                break;
            case Rotate :
                {
                    QList<JTPoint> pts;
                    const std::array<float, 6> ptf1 = {60,0,90,0,0,0};
                    JTPoint pt1(ptf1);
                    speak("Поворот");
                    pts.append(pt1);
                    m_RobotMotion->ParseTrackJT(pts, 30);
                }
                break;
            case StopParse :
                {
                    m_VoiceManage = false;
                    speak("Заканчиваю сеанс");
                }
                break;
            default:
                break;
            }
        }
    }
    UpdateSystemState();
}
//------------------------------------------------------------------------------
void VoiceParseForm::UpdateSystemState()
{
    ui->label_Status->setText("Распознано " + m_RespText);
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
}
