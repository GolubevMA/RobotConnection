
#ifndef KAWASAKIMOTION_H
#define KAWASAKIMOTION_H

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
#include "irobotmotion.h"

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


class KawasakiMotion : public QObject, public IRobotMotion
{
    Q_OBJECT
    Q_INTERFACES(IRobotMotion)

private:

    //матрица текущего полжения робота
    QMatrix4x4 m_CoordDecartMat;
    //текущая координта в декартовой системе
    DecartPoint m_CoordDecart;

    //текущаяя координата JT
    JTPoint m_CoordJT;
    //обьект решения задачи обратного позиционирования
    KinTaskSolver m_KinTaskSolv;


    ////флаг установления соедениея с роботм
    //bool m_Connected;
    //флаг активности рботта - на контроллере запущенна MC программа непрерывного режима
    bool m_Active;

    //------------------------------------------------
    //парметры атвоматичского режима (в автоматическом режиме очредь команд формируется на
    // стороне обработчика сканирования)
    //------------------------------------------------
    //ожиданиие обработки команды устновки точки
    int m_ContinousModeWait;
    int m_ContinousModeAck;
    //текущая команда, формиуремая при вызрве AddTrackPoint
    //после того как команда превышает максимальный размер происходит ее отпрака
    QString m_ContinousCommand;

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
    const int MAX_SOCKET_QUEUE_SIZE =  5;       // максимальная очередь
    QQueue<QString> m_queueWriteSocket;

    //codition для сихронизации слоотов соектов
    // (блокирует осоной поток, пока иницированные выховом отрытых функйи
    // отриытие или зарытие сокета не будут заврешены)
    QWaitCondition m_waitSockeSlot;
    // мьютек для condition (см документацию)
    QMutex m_conditionMutex;

    //таймут отртия зарытия сокета
    const int TIMEOUT_OPEN_CLOSE = 50;
    //сокет для отпраки команд контроллеру
    QTcpSocket *m_WorkSocket;
    //сокет для получения сотяния робота
    QUdpSocket *m_StateSocket;
    //порт udp клиента
    int m_UdpClientPort;

    // таймаут ответа клента
    const int  TIMEOUT_ANS_ROBOT  = 2000;
    //таймер ожиадния отвеота от клента
    QTimer *m_timerAnsTimeout;

    //тайм аут отпраки команды активности клиента
    const int TIMEOUT_COORD = 1000;
    //таймет отпрки команды актисности клиета
    QTimer *m_timerCmdTimeout;

    //команда запроса координиты
    QString m_CmdState = "UDPSTART ";
    QString m_status_ident = " STATE";

    //адресс сервера
    QString m_HostIp;
    //udp порт хоста
    int m_HostUdpPort;
    //tcp порт хоста
    int m_HostPort;
    //команда, на которую ожиается ответ
    QString m_wait_cmd;
    //масимальный размер команды 255 символов - 1 (раздлетилеь) - 5 - ident
    const int MAX_CMD_SIZE = 240;

//    // буффер в который считываем данные из фремйма
//    char RxBuffer[1024 * 14];
//    // здесь храним число данных в буфере
//    int RxBufferCount;
    //частота опроса
    int CoordFreq;

    //расет точки при перемещении канера вдоль оси (XYZ) без созранения положения сферического запятсья
    bool calcStepMove(int axis, float step, DecartPoint &res_pt);
    //формриуерм строку из точки
    QString pointToString(JTPoint &pt, int speed);

public:

    //число осей робота
    static const int MaxAxisCount = 6;

    //текущая позицяия Home
    //JTPoint m_HomePos;
    int HomeZOffset;
    int HomeXYOffset;

    explicit KawasakiMotion(QObject *parent = 0);
    ~KawasakiMotion();

    const JTPoint &GetCurrentJT() override {return m_CoordJT;}
    const DecartPoint &GetCurrentXYZ() override {return m_CoordDecart;}
    //const JTPoint &GetCurrentHome() {return m_HomePos;}
    int GetFreq() override {return  CoordFreq;}

    //прверка достижимости точки
    int checkPtIsValid(DecartPoint &pt) override;
    //флаг готовности робота - устанваливается если есть рсдениение с роботм
    //и если запущенна MC прогрмамма непервыног режима
    bool isReady() override;
    //проверка возможности оправки команды в авто режиме
    bool autoScanCmdEnable() override;

    //-------------------------------------
    //команды упралвения
    //-------------------------------------
    //ининициализация робота - отправка команды запуска непервыного режима
    void initRobot() override;
    //завршения MC прогрмамы непрерывного движеиня
    void closeRobot() override;
    //прервать текущую исполнмю команду
    void stopCommand() override;
    //добавление точки траектории
    int appendTrackPoint(DecartPoint pt, int speed) override;
    int sendTrackPoint() override;

    //выход в ноль
    bool moveHome(int speed) override;
    //пермещение в точку в угалх осей
    void movePointJT(JTPoint point, int speed) override;
    //перемещение в точку (в базисе XYZ)
    bool stepMoveXYZ(int axis, float step, int speed) override;
    int movePointXYZ(DecartPoint point,  int speed) override;
    void ParseTrackJT(QList<JTPoint> &points, int speed) override;
    int ParseTrackXyz(QList<DecartPoint> points, int speed) override;
    //перемещение на шаг в углах осей
    //void StepMoveJT(int axis, int step, int speed);
    //пермещение на шаг в базисе XYZ

    //метод добавлеят команлду в очердь и осущемтвеляет межпоотоный вызов
    // функции отправки данных по tcp
    void sendCmdEvent(QString cmd);
    //очистка очережи коман
    void clearCmdQueue();

    //метод вызывают создаение сокетов в через межпоточный вызов
    bool createConnection(QString ip, int port_tcp, int port_udp) override;
    void closeConnection() override;
    bool isConnected() override;


//слоты выполняемые в отднльном потоке
private slots :
    //создаеие сокета (в случае tcp  - установление соедниение)
    void slotSocketOpen();
    //закрытие сокета
    void slotSocketClose();
    //отпрвка команды в tcp сокет
    void writeCommand();   
    //отправка команды активности клиента в udp сокет
    void writeUdpReqest();
    void timerAnsTimeout();
    void checkResponse();
    void Disconnect();

signals :
    void coordChanged();
    void autoModeEvent();

};

#endif // ROBOTMOTION_H
