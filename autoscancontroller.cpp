#include "autoscancontroller.h"
//------------------------------------------------------------------------------
AutoScanController::AutoScanController(RobotMotion* robot, /*KinTaskSolver *solver,*/ QObject *parent)
    : QObject(parent)
{
    m_RobotMotion = robot;
    //m_KinSolver = solver;
    //обработка происходит в слоте onScanProcess по сигналу подтврежиения команды набора точек
    // в птоке обьекта AutoScanController (в потоке UI)
    connect(m_RobotMotion, SIGNAL(autoModeEvent()), this, SLOT(onScanProcess()), Qt::QueuedConnection);
    //подключаем сигнал таймера ожидаения ответа к с
    m_WaitResonseTimer = new QTimer();
    connect(m_WaitResonseTimer, SIGNAL(timeout()), this, SLOT(ScanerNoRespnse()));
}
//------------------------------------------------------------------------------
void AutoScanController::setScanParams(QList<DecartPoint> &points, DecartPoint start_pt, int scan_speed, int lines_count)
{
    m_StartScanPt =  start_pt;
    m_ScanSpeed = scan_speed;
    m_ScanLineCount = lines_count;
    m_ScanLine.clear();
    //прибавляем к точкам начала линий
//    foreach(DecartPoint pt, &points) {
//        DecartPoint rel_pt = pt;
//        rel_pt.setX(pt.x() + m_StartScanPt.x());
//        rel_pt.setX(pt.y() + m_StartScanPt.y());
//        rel_pt.setX(pt.z() + m_StartScanPt.z());
//        m_ScanLine.append(rel_pt);
//    }
}
//------------------------------------------------------------------------------
//пытаемся запусить режим сканирования
//------------------------------------------------------------------------------
void AutoScanController::startScan()
{ 
    //флаг повтороного зароса
    try {
        //есил нест свыяи с роботм - выйдем
        if (!m_RobotMotion->isConnected()) throw ScanError::NoConnection;

        //очащем очередь команд перед запуском неперрывного режима
        m_RobotMotion->clearCmdQueue();
        //запускаем непрервынй режим
        if  (m_RobotMotion->StartContinousMode(m_ScanSpeed)) throw ScanError::PrepareMcRunning;

        m_ScanState = Homing;
        //ошибка процесса сканирования
        m_ScanErrorState = NoError;
        //активурем таймер простоя
    }
    catch(int err)  {
        m_ScanErrorState = err;
    }
}
//------------------------------------------------------------------------------
void AutoScanController::stopScan()
{
//    if (!m_running) return;
//    m_running = false;
//    if (m_robot) m_robot->StopAutoMdoe();
}
//------------------------------------------------------------------------------
void AutoScanController::onScanProcess()
{   
//    try  {
//        //сбросим таймер ожидания ответа от сканера
//        m_WaitResonseTimer->start();
//        switch (m_ScanState)
//        {
//        case Homing :
//            {
//                if (m_RobotMotion->HomeContinous()) throw HomeErrror;
//                //заупскаем ождиние выхода в 0
//            }
//            break;
//        //запсиь линии скана в напрввлении вперед/назад
//        case ScanLineForward :
//        {
//            static QList<DecartPoint>::const_iterator it = m_ScanLine.cbegin();
//            //проходимся по списк в прямом напрвадении
//            //формурем команду
//            DecartPoint pt = it.

//}
//        }
//        case ScanLineReverse :
//        {
//        }
//        //перемещение сканера в точку сканирвоаничя следующей линии на слеудющую линию
//        case ScanWaitNextLine :
//            break;
//        }
//    }
//    catch(int code) {

//    };
}
//------------------------------------------------------------------------------
