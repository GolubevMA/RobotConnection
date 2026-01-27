#include "voiceresponser.h"
#include <QRegularExpression>

VoiceResponser::VoiceResponser(QObject *parent) : QObject(parent)
{
    //инициализируем Vosk
    m_VoskModel= vosk_model_new("j:\\WorkProjects\\RoboScan\\vosk-model-small-ru-0.22");
    m_VoskRecognizer = vosk_recognizer_new(m_VoskModel, 16000.0);

    //настраиввааем поток - обработчик
    m_Thread = new QThread(); m_Thread->start();
    //переносим этот объект в новый поток
    connect(m_Thread, SIGNAL(started()), this, SLOT(initAudio()));
    this->moveToThread(m_Thread);

}
//-----------------------------------------------------------------------------
VoiceResponser::~VoiceResponser()
{
    m_Thread->exit();
    m_Thread->wait();
    delete m_Thread;

    vosk_recognizer_free(m_VoskRecognizer);
    vosk_model_free(m_VoskModel);
}
//------------------------------------------------------------------------------
//инициализация обработчика аудиопотока
//------------------------------------------------------------------------------
void VoiceResponser::initAudio()
{
    //настрйаиваем формат аудио
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }

    m_AudioInput = new QAudioInput(format, this);
    //ослеживаем изменение состояния обьекта записи
    connect(m_AudioInput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
}
//------------------------------------------------------------------------------
bool VoiceResponser::isActive() {return m_AudioInput->state() == QAudio::ActiveState;}
//------------------------------------------------------------------------------
//обработчик изменения состояния сканера
//------------------------------------------------------------------------------
void VoiceResponser::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::StoppedState:
            if (m_AudioInput->error() != QAudio::NoError) {
                 emit UpdateState(-1);
              }
              else {
                  emit UpdateState(0);
              }
              break;
          case QAudio::ActiveState:
                emit UpdateState(1);
              break;

          default :
              break;
      }
}
//------------------------------------------------------------------------------
//слот обработки аудио потока
//------------------------------------------------------------------------------
void VoiceResponser::voiceRecognize()
{
    //вычитыаем сырые данные из буффера
    QByteArray data = m_AudioRecorder->readAll();
    if (!data.isEmpty())
    {
        //регулярное выражение для вычлеения фразы
        QRegularExpression re(":\\s*\"([^\"]+)\"");
        if (vosk_recognizer_accept_waveform(m_VoskRecognizer, data.data(), data.size()))
        {
            // Если фраза закончена
            QString result = vosk_recognizer_result(m_VoskRecognizer);
            qDebug() << "Full text " << result;
            //вычленияем фразу
            QRegularExpressionMatch m = re.match(result);
            if (m.hasMatch()) {
                QString value = m.captured(1);
                emit total_result(value);
                //разирам команду со словарем
            }
        }
        else {
            // Промежуточное распознавание (пока человек говорит)
            QString partial = vosk_recognizer_partial_result(m_VoskRecognizer);
            //вытаскиваем текст из кавычек
            QRegularExpressionMatch m = re.match(partial);
            if (m.hasMatch()) {
                QString value = m.captured(1);
                emit partial_result(value);
            }
        }
    }
}
//------------------------------------------------------------------------------
//основалвиваем обработку
//------------------------------------------------------------------------------
void VoiceResponser::stopRecognize()
{
    if (m_AudioRecorder) {
        disconnect(m_AudioRecorder, SIGNAL(readyRead()), this, SLOT(voiceRecognize()));
        m_AudioInput->stop();
        m_AudioRecorder = nullptr;
        qDebug() << "stappoing";
    }
}
//------------------------------------------------------------------------------
//запускаем обработку
//------------------------------------------------------------------------------
void VoiceResponser::startRecognize()
{
    qDebug() << "starting";
    m_AudioRecorder = m_AudioInput->start();
    if (m_AudioRecorder != NULL) {
        //соединям синал увеличения данных в буффере обработки потока со слотом обработчиком
        connect(m_AudioRecorder, SIGNAL(readyRead()), this, SLOT(voiceRecognize()), Qt::QueuedConnection);
    }
}
