#ifndef VOICEPARSEFORM_H
#define VOICEPARSEFORM_H

#include <QWidget>
#include "robotmotion.h"
#include "voiceresponser.h"
#include <QIcon>

namespace Ui {
class VoiceParseForm;
}

class VoiceParseForm : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceParseForm(QWidget *parent = nullptr);
    ~VoiceParseForm();

    void setRobotObject(RobotMotion *obj);
    void speak(QString text);

public slots :
    void partialResult(QString res);
    void totalResult(QString res);
    void updateState(int st);
    void UpdateSystemState();

private slots :
    void on_pushButton_Recognize_clicked();

    void on_pushButton_Recognize_2_clicked();

private:
    //обьект управления роботом
    RobotMotion *m_RobotMotion;
    //обьект распознавания команд
    VoiceResponser *m_VoiceParser;

    //флаг начала раснознания новго отрывка (если пришел пустной отрывок - флаг сбрасывается)
    bool m_NewPartRec;
    //текщуий распознаыйт текст
    QString  m_RespText;

    //флаг режима голосового управления
    bool m_VoiceManage;

    //команды для распознавания в виде наборов сининимеичных слов
    QSet<QString> m_VoiceManageStartCmd;
    QSet<QString> m_GreetingsCmd;
    QSet<QString> m_VoiceManageEndCmd;

    //иконки
    QIcon *m_OffIcon;
    QIcon *m_OnIcon;
    QIcon *m_SpeakIcon;

    Ui::VoiceParseForm *ui;

    void initCmdDictionary();
};

#endif // VOICEPARSEFORM_H
