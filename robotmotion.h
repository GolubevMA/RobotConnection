#ifndef ROBOTMOTION_H
#define ROBOTMOTION_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <QWaitCondition>
#include <QtNetwork/QUdpSocket>
#include "vars.h"
#include <QVector3D>
#include <QMatrix4x4>
#include <QtNetwork/QTcpSocket>

/*
 * Класс управления движением робота
    События обрабатываются в отельном потоке.
    Для передаче управления потоку из отрытых метотдов (межпоотчный вызов) используется соьытие таймера
    Команда считеися выполнеой, как только получен ответ от контролеллера о том, что комнда принята
    Контролллер передает свои координаты и состояние выполнямой MOtionProgramm (false - не выполняктся. true - выполняется)

    Слот отправки команды вызывается по таймеру с чатотой 500 гц, если не ждем отчетв на команду от робота
    и робот не занят выполненим команлы движения - отпраляемя команду из очереди, если была отправленна команда, робот
    выполнят команду движения и инницированн остнаовка двжиения - отправлеям команду Break, инае отравляем коменду запроса коорднитаы
    (при отправее команды зоаарса коорита не происходит поднятие флагов wait и ack - поток не контрлллирует успешность отпра=вки команды)
    (cлелано так, поскольку recv функция коннтрллера блокриует программу, если нет входных данных миниму на скенуу)

*/


class RobotMotion : public QObject
{
    Q_OBJECT

private:

    //матрица текущего полжения робота
    QMatrix4x4 m_CoordDecartMat;
    //текущая координта в декартовой системе
    DecartPoint m_CoordDecart;

    //текущаяя координата JT
    JTPoint m_CoordJT;
    //обьект решения задачи обратного позиционирования
    KinTaskSolver m_KinTaskSolv;

    //------------------------------------------------
    //состояние запроса движения
    //------------------------------------------------
    //флаг выполнения команды движения
    bool m_MotionProgramm;
    //флаг остановки выполения текущей команды двжиения
    bool m_StopMotionProg;

    //------------------------------------------------
    //парметры автоматическокго режима
    //------------------------------------------------
    //режми формирования таректории - на контролрее запущенна MC программа, ринимающая точки траектории
    bool m_AutoMode;
    //ожиданиие обработки команды устновки точки
    int m_AutoModeWait;
    int m_AutoModeAck;

    int CoordFreq;

    //------------------------------------------------
    //статус ожидания ответа от робоьа
    //------------------------------------------------
    const int  STATE_NO_WAIT_DATA  = 0;       // данных не ожидается
    const int  STATE_WAIT_ANS  = 1;           // ожидаем ответ от робота
    int m_waitStatus;

    //поток в которм реализуются все обработчикии событый таймера
    // обрабочтикми событий таймера являются слоты
    // которые реализуют примем/отправку данных в сокет
    QThread *mThread;

    //мьтекс для синхронизации межпоточных вызовов
    // (публичные функции находящиеся в основом потоке и
    // методы класса используют общеие обьекты )
    // для доступа к кторым надо накинуть этот мьютекс
    QMutex m_mutexObj;

    //очередь данных для записи в соект
    const int MAX_SOCKET_QUEUE_SIZE =  30;       // максимальная очередь
    QQueue<QString> m_queueWriteSocket;

    //codition для сихронизации слоотов соектов
    // (блокирует осоной поток, пока иницированные выховом отрытых функйи
    // отриытие или зарытие сокета не будут заврешены)
    QWaitCondition m_waitSockeSlot;
    // мьютек для condition (см документацию)
    QMutex m_conditionMutex;

    //таймут отртия зарытия сокета

    const int TIMEOUT_OPEN_CLOSE = 50;
    //сокет для взаиомдейтвя с ptaxel
    QTcpSocket *m_WorkSocket;

    // таймаут ответа клента
    const int  TIMEOUT_ANS_ROBOT  = 2000;
    //таймер ожиадния отвеота от клента
    QTimer *m_timerAnsTimeout;

    //тайм аут запроса отпраки команжды мс
    const int TIMEOUT_COORD = 10;
    //тайет отпрки команды
    QTimer *m_timerCmdTimeout;
    //команда запроса координиты
    QString m_CmdState = "STATE ;";
    QString m_CmdStop = "STOP ;";
    QString m_status_ident = " STATE";

    //адресс клиента
    QString m_HostIp;
    int m_HostPort;
    //команда, на которую ожиается ответ
    QString m_wait_cmd;
    //масимальный размер команды 255 символов - 1 (раздлетилеь) - 5 - ident
    const int MAX_CMD_SIZE = 249;

    // буффер в который считываем данные из фремйма
    char RxBuffer[1024 * 14];
    // здесь храним число данных в буфере
    int RxBufferCount;

    //void parseResponse(QString &resp);

public:

    //число осей робота
    static const int MaxAxisCount = 6;

    RobotMotion(QObject *parent = 0);
    ~RobotMotion();

    const JTPoint &GetCurrentJT() {return m_CoordJT;}
    const DecartPoint &GetCurrentXYZ() {return m_CoordDecart;}
    int GetFreq() {return  CoordFreq;}

    //прверка достижимости точки
    int checkPtIsValid(DecartPoint &pt);

    //-------------------------------------
    //команды упралвения
    //-------------------------------------
    //вкл/выкл мотора
    //void MotorOnOF(bool on, QString &status);
    //перемещение на шаг в углах осей
//    void StepMoveJT(int axis, int step, int speed);
//    //пермещение на шаг в базисе XYZ
//    void StepMoveXYZ(int axis, int step, int speed);

    //пермещение в точку в угалх осей
    void MovePointJT(JTPoint point, int speed);
    //перемещение в точку (в базисе XYZ)
    int MovePointXYZ(DecartPoint point,  int speed);
    void SetZero();

    void StartBuild(int speed);
    void StopBuild();
    //отправлем массив точек в режиме потсроения траектории
    void ParseTrackJT(QList<JTPoint> &points, int speed);
    int ParseTrackXyz(QList<DecartPoint>, int speed);
    //прервать текущую исполнмю команду
    void stopCommand();

    //метод добавлеят команлду в очердь и осущемтвеляет межпоотоный вызов
    // функции отправки данных по udp
    void sendCmdEvent(QString cmd);
    //метод вызывают создаение сокетов в через межпоточный вызов
    bool createConnection(QString ip, int port);
    void closeConnection();
    bool isConnected();
    bool autopilotCmdEnable();

//слоты выполняемые в отднльном потоке
private slots :
    //создаеие сокета (в случае tcp  - установление соедниение)
    void slotSocketOpen();
    //закрытие сокета
    void slotSocketClose();
    //отпрвка команды в сокет
    void writeCommand();
    void breakCommand();
    void timerAnsTimeout();
    void checkResponse();
    void Disconnect();

signals :
    void coordChanged();
    void transaction(bool);
    void buildStarted();

};

#endif // ROBOTMOTION_H
