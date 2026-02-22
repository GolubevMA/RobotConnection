#ifndef IROBOTMOTION_H
#define IROBOTMOTION_H

#include <QObject>
#include "jtpoint.h"
#include "decartpoint.h"


/*
    Интерфейс управления роботом
*/

class IRobotMotion
{
public:
    virtual ~IRobotMotion() = default;

    virtual const JTPoint &GetCurrentJT() = 0;
    virtual const DecartPoint &GetCurrentXYZ() = 0;
    virtual int GetFreq() = 0;

    //прверка достижимости точки
    virtual int checkPtIsValid(DecartPoint &pt) = 0;
    //флаг готовности робота - устанваливается если есть рсдениение с роботм
    //и если запущенна MC прогрмамма непервыног режима
    virtual bool isReady() = 0;
    //проверка возможности оправки команды в авто режиме
    virtual bool autoScanCmdEnable() = 0;

    //-------------------------------------
    //команды упралвения
    //-------------------------------------
    //ининициализация робота - отправка команды запуска непервыного режима
    virtual void initRobot() = 0;
    //завршения MC прогрмамы непрерывного движеиня
    virtual void closeRobot() = 0;
    //прервать текущую исполнмю команду
    virtual void stopCommand() = 0;
    //добавление точки траектории
    virtual int appendTrackPoint(DecartPoint pt, int speed) = 0;
    virtual int sendTrackPoint() = 0;

    //выход в ноль
    virtual bool moveHome(int speed) = 0;
    //пермещение в точку в угалх осей
    virtual void movePointJT(JTPoint point, int speed) = 0;
    //перемещение в точку (в базисе XYZ)
    virtual bool stepMoveXYZ(int axis, float step, int speed) = 0;
    virtual int movePointXYZ(DecartPoint point,  int speed) = 0;
    virtual void ParseTrackJT(QList<JTPoint> &points, int speed) = 0;
    virtual int ParseTrackXyz(QList<DecartPoint> points, int speed) = 0;
    //перемещение на шаг в углах осей
    //void StepMoveJT(int axis, int step, int speed);

    //метод вызывают создаение сокетов в через межпоточный вызов
    virtual bool createConnection(QString ip, int port_tcp, int port_udp) = 0;
    virtual void closeConnection() = 0;
    virtual bool isConnected() = 0;

};

// Регистрируем интерфейс в системе Qt (нужен уникальный ID)
Q_DECLARE_INTERFACE(IRobotMotion, "com.roboscan.IRobotMotion")

#endif // ROBOTMOTION_H
