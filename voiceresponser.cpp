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
//сарвние по алгоритму Джаро-Винклера
//------------------------------------------------------------------------------
double VoiceResponser::compareString(QString &s1, QString &s2)
{
    int len1 = s1.length();
    int len2 = s2.length();
    if (len1 == 0) return len2 == 0 ? 1 : 0;

    // Расчет окна совпадения
    int match_distance = std::max(len1, len2) / 2 - 1;
    QVector<bool> s1_matches(len1, false);
    QVector<bool> s2_matches(len2, false);

    int matches = 0;
    for (int i = 0; i < len1; i++)
    {
        int start = std::max(0, i - match_distance);
        int end = std::min(i + match_distance + 1, len2);
        for (int j = start; j < end; ++j)
        {
            if (!s2_matches[j] && s1[i] == s2[j])
            {
                s1_matches[i] = true;
                s2_matches[j] = true;
                matches++;
                break;
            }
        }
    }
    //если совпадений не обнаружено - возвращем ноль
    if (matches == 0) return 0;

   // Считаем транспозиции
   double transpositions = 0;
   int k = 0;
   for (int i = 0; i < len1; i++) {
       if (s1_matches[i]) {
           while (!s2_matches[k]) k++;
           if (s1[i] != s2[k]) transpositions++;
           k++;
       }
   }
    double jaro = (matches / (double)len1 +
                  matches / (double)len2 +
                  (matches - transpositions / 2.0) / matches) / 3.0;

    // Коэффициент Винклера
   double p = 0.1;
   // Длина общего префикса (max 4)
   int l = 0;
   int max_l = std::min({len1, len2, 4});
   for (int i = 0; i < max_l; i++) {
       if (s1[i] == s2[i]) l++;
       else break;
   }
    return jaro + l * p * (1.0 - jaro);
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

    QList<QAudioDeviceInfo>devs = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach(QAudioDeviceInfo inf, devs) {
        qDebug() << " dev " << inf.deviceName();
    }

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
