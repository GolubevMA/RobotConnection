#include "autoscancontroller.h"
//------------------------------------------------------------------------------
AutoScanController::AutoScanController(RobotMotion* robot, QObject *parent)
    : QObject(parent)
{
    m_RobotMotion = robot;

    m_ScanFlag = false;
    m_ScanState = StartHoming;
    //ошибка процесса сканирования
    m_ScanErrorState = NoError;
    m_RedyToScan = false;

    //m_KinSolver = solver;
    //обработка происходит в слоте onScanProcess по сигналу подтврежиения команды набора точек
    // в птоке обьекта AutoScanController (в потоке UI)
    connect(m_RobotMotion, SIGNAL(autoModeEvent()), this, SLOT(onScanProcess()), Qt::QueuedConnection);

    //подключаем сигнал таймера ожидаения ответа к слоту обраточкиу
    m_WaitResonseTimer = new QTimer();
    connect(m_WaitResonseTimer, SIGNAL(timeout()), this, SLOT(ScanerNoRespnse()));
}
//------------------------------------------------------------------------------
void AutoScanController::setScanParams(QList<DecartPoint> &points, QVector3D start_pt, int scan_speed, int lines_count)
{
    m_StartScanPt =  start_pt;
    m_ScanSpeed = scan_speed;
    m_ScanLineAmout = lines_count;
    m_ScanLine.clear();
    //прибавляем к точкам начала линий
    foreach(DecartPoint pt, points) {
        DecartPoint rel_pt = pt;
        rel_pt.setX(pt.x() + m_StartScanPt.x());
        rel_pt.setX(pt.y() + m_StartScanPt.y());
        rel_pt.setX(pt.z() + m_StartScanPt.z());
        m_ScanLine.append(rel_pt);
    }
    m_RedyToScan = true;
}
//------------------------------------------------------------------------------
//пытаемся запусить режим сканирования
//------------------------------------------------------------------------------
int AutoScanController::startScan()
{ 
    //проверяем что система готва к сканиорванию
    //есть загруженная модель
    if (!m_ScanFlag && m_RedyToScan)
    {
        m_ScanErrorState = 0;
        m_ScanState =  ScanSetup;
        m_ScanFlag = true;
        emit scanState(m_ScanFlag, m_ScanErrorState);
        QTimer::singleShot(0, this, SLOT(onScanProcess()));
        return 1;
    }
    else if (m_RedyToScan) return  -1;
    else return  0;
}
//------------------------------------------------------------------------------
void AutoScanController::stopScan()
{
    if (m_ScanFlag) m_ScanFlag = false;
}
//------------------------------------------------------------------------------
//процесс сканирования
//------------------------------------------------------------------------------
void AutoScanController::onScanProcess()
{   
    //итератор для прохждения по скипску точек
    static  QListIterator<DecartPoint> scanIter = QListIterator<DecartPoint>(m_ScanLine);
    if (m_ScanFlag)
    {
        try  {
            //сбросим таймер ожидания ответа от сканера
            m_WaitResonseTimer->start(5000);
            switch (m_ScanState)
            {
            case ScanSetup :
                {
                    //если сканер не активен - выйдем
//                    if (!m_RobotMotion->isConnected()) throw ScanError::NoConnection;
//                    if (!m_RobotMotion->isReady()) throw ScanError::NoConnection;
                    //устаановилеаем стостяниее режима
                    m_ScanState = StartHoming;
                    //ошибка процесса сканирования
                    m_ScanErrorState = NoError;
                    m_ScanLineDir = false;
                    m_ScanCurrLine = -1;
                    //активурем таймер простоя
                    m_WaitResonseTimer->start();
                    QTimer::singleShot(0, this, SLOT(onScanProcess()));
                }
                break;
            case StartHoming :
                {
                    if (!m_RobotMotion->moveHome(m_ScanSpeed)) throw HomeErrror;
                    //заупскаем ождиние выхода в 0
                    m_ScanState = WaitHoming;
                    qDebug() << "waitng homeg";
                    emit scanState(m_ScanFlag, m_ScanState);
                }
                break;
            case WaitHoming :
                {
                    const JTPoint &cur = m_RobotMotion->GetCurrentJT();
                    const JTPoint &targ = m_RobotMotion->GetCurrentHome();
                    //если стоим в нужной точке
                    if (JTPoint::equals(cur, targ, 1.0f)) {
                        //заупскаем ождиние выхода на нчало линии сканирования
                        m_ScanState = ScanWaitNextLine;
                        qDebug() << " waiwed ";
                    }
                    emit scanState(m_ScanFlag, m_ScanState);
                }
                break;
            //запсиь линии скана в напрввлении вперед/назад
            case ScanLineForward :
                {
                    if (m_ScanLineDir)
                    {
                        //прохдомся по точка траектории
                        while (scanIter.hasNext()) {
                            DecartPoint target = scanIter.next();
                            //перемещаем робота в точку
                            if (!m_RobotMotion->appendTrackPoint(target, m_ScanSpeed))  {
                                //если точку добавить не удалось - команда сформирована - ждем подтвержения с последубщим вызом слота
                                //cсдвинем итератор назад
                                scanIter.previous();
                                break;
                            }
                        }
                    }
                }
                break;
            case ScanLineReverse :
                {

                }
                break;
            //перемещение сканера в точку сканирвоаничя следующей линии на слеудющую линию
            case ScanWaitNextLine :
                {
                    //зесдь всегда считаем что вышли на новую линию сканирвоания
                    //увлеичиаем чсило линий - меням напрвление
                    m_ScanCurrLine++;
                    if (m_ScanCurrLine >= m_ScanLineAmout - 1) {
                        m_ScanFlag =false;
                        scanEnding(NoError);
                    }
                    else {
                        //сбрасываем итератор
                        if (m_ScanLineDir) scanIter.toFront();
                        else  scanIter.toBack();
                    }
                }
                break;
            }
        }
        catch(int code) {
            m_ScanFlag =false;
            scanEnding(code);
        };
    }
    else {
        scanEnding(NoError);
    }
}
//------------------------------------------------------------------------------
//заврешение сканрования
//------------------------------------------------------------------------------
void AutoScanController::scanEnding(int exit_code)
{
    //отсновим таймер ождиания
    m_WaitResonseTimer->stop();
    //отсновим двжиение
    m_RobotMotion->stopCommand();
    //запомним сотстяние ошибки
    m_ScanErrorState = exit_code;
    //сигнаол обновления ui
    scanState(m_ScanFlag, m_ScanErrorState);
}
//------------------------------------------------------------------------------
//тайме активности сканера
//------------------------------------------------------------------------------
void AutoScanController::ScanerNoRespnse()
{
    if (m_ScanFlag) m_ScanFlag =false;
    scanEnding(CmdTimeOut);
}
