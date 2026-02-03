#ifndef VOICERESPONSER_H
#define VOICERESPONSER_H
//-----------------------------------------------------------------------------
#include <QObject>
#include <QtMultimedia>
#include <QtMultimedia/QAudioFormat>
#include <QAudioInput>
#include "vosk_api.h"
#include <QIODevice>
//-----------------------------------------------------------------------------
//класс инкапсулирующий обработку голосовых команд
//-----------------------------------------------------------------------------
class VoiceResponser : public QObject
{
    Q_OBJECT
public:
    explicit VoiceResponser(QObject *parent = nullptr);
    ~VoiceResponser();

    void stopRecognize();
    void startRecognize();
    bool isActive();
    static double compareString(QString &s1, QString &s2);

private slots :
    void handleStateChanged(QAudio::State newState);
    void voiceRecognize();
    void initAudio();

signals:
    void partial_result(QString res);
    void total_result(QString res);
    void UpdateState(int st);

private:

    //обьект записи звука
    QAudioInput *m_AudioInput;
    //модель распознавания голоса
    VoskModel *m_VoskModel;
    VoskRecognizer *m_VoskRecognizer;
    //обьект обработки потока audio
    QIODevice *m_AudioRecorder;
    //поток в котором происходит обработка событий
    QThread *m_Thread;



};

#endif // VOICERESPONSER_H
