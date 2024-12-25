    #ifndef TRobotMotion_H
#define TRobotMotion_H

#include <QObject>
#include <QThread>
#include "winsock2.h"
#include "windows.h"

/*
    Класс инкапсулирующий управление робоитом
     реалихует интерфейc команд упрвления
     поддерживается какуправление в классическом режиме (общение с контролерром робота поTCPIP)
     так и управлениее в режиме эмуляции
     расчтывает пределные значения короодинат перед тем как совершить движение
     если при поапытке выполнить движение получили ошибку - остновим прем команд
     до тех пор, пока пользовтель не подтвердит ошибку
*/

class TRobotMotion : public QThread
{
    Q_OBJECT
public:

    enum MotioType {JOIUNT,  BASE, TOOL};


    //параметры движения
    int MotionMode = MotioType::JOIUNT;
    float MotionSpeed;


    QString IPAddres;
    bool Terminate;

    explicit TRobotMotion(QObject *parent = nullptr, QString ip = "");
    ~TRobotMotion();

    //комаеды упралвения
    int MotorOnOF(bool on, QString &status);
    int MovePoint(int coord_type, QVector<int> point, QString &status);
    int StepMove(int coord_type, int axis, int step, QString &status);
    void run() override;

private :

    const int CmbBufSize = 10;  //макисмальное колиичесвто команд в очереди
    int CurrentCmdCount;        //текущее колличесвто обрабатывеемых команд

    QString MotionCmd;
    int  MotionCommandExitCode;
    QString MotionCommandStatus;


    //параметры соединения
    bool MotionCommandFree;
    bool MotionCommand;           //флаг наличия созданной комадны
    bool MotionCommandWaitAnswer; //флаг ожидания ответ на команлу

    SOCKET DevSock;
    SOCKADDR_IN serv_addr;
    bool Active;

    bool CreateSocket();
    bool WaitData();
    bool WaitConnection();
    int ProcessCommand(QString str, QString &state);


signals:
    void updatePos(QString pos);

public slots:
};

#endif // TRobotMotion_H
