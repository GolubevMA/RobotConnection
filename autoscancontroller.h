#ifndef AUTOSCANCONTROLLER_H
#define AUTOSCANCONTROLLER_H
//-----------------------------------------------------------------------------
#include <QObject>
#include <QQueue>
#include "vars.h"
#include "robotmotion.h"
#include <QTimer>
//-----------------------------------------------------------------------------
//класс инкапсулирующий управление сканированием
//-----------------------------------------------------------------------------
class AutoScanController : public QObject
{
    Q_OBJECT
public:
    //стояния сканирвоания
    enum ScanState {Homing, ScanLineForward, ScanLineReverse, ScanWaitNextLine};

    //ошбика режима автоматчиеского сканироваия
    enum ScanError {NoConnection, PrepareMcRunning, HomeErrror, NoError};

    explicit AutoScanController(RobotMotion *robot, /*KinTaskSolver  *solver*,*/ QObject *parent=nullptr);

    //устанваливаем парматры сканировнаяия
    void setScanParams(QList<DecartPoint> &points, DecartPoint start_pt, int scan_speed, int lines_count);


public slots:

    //процедуры зауска / остановки сканирования
    void startScan();
    void stopScan();

private slots:
    void onScanProcess();

private:

    //состояние процесса сканирования
    int m_ScanState;
    //ошибка процесса сканирования
    int m_ScanErrorState;
    //таймер прстоя
    QTimer *m_WaitResonseTimer;

    //обьект управлениея движением робота
    RobotMotion *m_RobotMotion;
    //обьект решения обратной задачи кинметики
    //KinTaskSolver *m_KinSolver;

     //текущуая линия (впосдледствие сдеалть через сплайн)
    QList<DecartPoint> m_ScanLine;
    //число линий сканирования
    int m_ScanLineCount;
    //точка начала сканирования
    DecartPoint m_StartScanPt;
    int m_ScanSpeed;


};

#endif // AUTOSCANCONTROLLER_H
