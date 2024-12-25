#ifndef TCONNECTIONTHREAD_H
#define TCONNECTIONTHREAD_H

#include <QObject>
#include <QThread>
#include "winsock2.h"
#include "windows.h"

/*
*/

class TConnectionThread : public QThread
{
    Q_OBJECT
public:


    QString IPAddres;
    bool MotionCommandFree;
    bool MotionCommand;           //флаг наличия созданной комадны
    bool MotionCommandWaitAnswer; //флаг ожидания ответ на команлу

    const int CmbBufSize = 10;  //макисмальное колиичесвто команд в очереди
    int CurrentCmdCount;        //текущее колличесвто обрабатывеемых команд

    QString MotionCmd;
    int  MotionCommandExitCode;
    QString MotionCommandStatus;

    SOCKET DevSock;
    SOCKADDR_IN serv_addr;

    bool Active;
    bool Terminate;


    explicit TConnectionThread(QObject *parent = nullptr, QString ip = "");
    ~TConnectionThread();

    int StepMove(int coord_type, int axis, int step, QString &status);
    int ProcessCommand(QString str, QString &state);

    bool CreateSocket();
    bool WaitData();
    bool WaitConnection();

    void run() override;

signals:
    void updatePos(QString pos);

public slots:
};

#endif // TCONNECTIONTHREAD_H
