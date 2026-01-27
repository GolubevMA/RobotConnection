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

public slots :
    void partialResult(QString res);
    void totalResult(QString res);
    void updateState(int st);

private slots :
    void on_pushButton_Recognize_clicked();

private:
    //обьект управления роботом
    RobotMotion *m_RobotMotion;
    //обьект распознавания команд
    VoiceResponser *m_VoiceParser;
    //флаг раснознания новго отрывка (если пришел пустной отрывок - флаг сбрасывается)
    bool m_NewPartRec;

    //иконки
    QIcon *m_OffIcon;
    QIcon *m_OnIcon;
    QIcon *m_SpeakIcon;

    Ui::VoiceParseForm *ui;
};

#endif // VOICEPARSEFORM_H
