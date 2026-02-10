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
    enum ScanState {ScanSetup, StartHoming, WaitHoming,  ScanLineForward, ScanWaitLineForward, ScanLineReverse, ScanWaitLineReverse, ScanWaitNextLine};

    //ошбика режима автоматчиеского сканироваия
    enum ScanError {NoConnection, PrepareMcRunning, HomeErrror, CmdTimeOut, NoError};

    explicit AutoScanController(RobotMotion *robot, QObject *parent=nullptr);

    //устанваливаем парматры сканировнаяия
    void setScanParams(QList<DecartPoint> &points, QVector3D start_pt, int scan_speed, int lines_count);


public slots:

    //процедуры зауска / остановки сканирования
    int startScan();
    void stopScan();

private slots:
    void onScanProcess();
    void ScanerNoRespnse();

private:

    //состояние процесса сканирования
    int m_ScanState;
    //ошибка процесса сканирования
    int m_ScanErrorState;
    //таймер прстоя
    QTimer *m_WaitResonseTimer;
    bool m_RedyToScan;

    //разрешение сканирования
    bool m_ScanEnable;
    //флаг режима скнаирования
    bool m_ScanFlag;
    //напправление сканирования линии
    bool m_ScanLineDir;
    //теущая линия скнаирования
    int m_ScanCurrLine;

    //обьект управлениея движением робота
    RobotMotion *m_RobotMotion;
    //обьект решения обратной задачи кинметики
    //KinTaskSolver *m_KinSolver;

     //текущуая линия (впосдледствие сдеалть через сплайн)
    QList<DecartPoint> m_ScanLine;
    //число линий сканирования
    int m_ScanLineAmout;
    //точка начала сканирования
    //DecartPoint m_StartScanPt;
    QVector3D m_StartScanPt;
    int m_ScanSpeed;

    //завреншение сканирвоания
    void scanEnding(int code);

signals :
    void scanState(bool scan_proc, int err_state);

};

#endif // AUTOSCANCONTROLLER_H
