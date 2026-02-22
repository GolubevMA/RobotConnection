#include "autoscancontroller.h"
//------------------------------------------------------------------------------
AutoScanController::AutoScanController(KawasakiMotion* robot, QObject *parent)
    : QObject(parent)
{
    m_RobotMotion = robot;

    m_ScanFlag = false;
    m_ScanEnable = false;
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
        rel_pt.setY(pt.y() + m_StartScanPt.y());
        rel_pt.setZ(pt.z() + m_StartScanPt.z());
        qDebug() << " x " << rel_pt.x() << " y " << rel_pt.y() << " z " << rel_pt.z();
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
        m_ScanEnable = true;
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
    if (m_ScanFlag && m_ScanEnable) {
        m_ScanEnable = false;
    }
}
//------------------------------------------------------------------------------
//процесс сканирования
//------------------------------------------------------------------------------
void AutoScanController::onScanProcess()
{   
    //итератор для прохждения по скипску точек
    static  QListIterator<DecartPoint> scanIter = QListIterator<DecartPoint>(m_ScanLine);
    if (m_ScanFlag && m_ScanEnable)
    {
        try  {
            //сбросим таймер ожидания ответа от сканера
            m_WaitResonseTimer->start(5000);
            switch (m_ScanState)
            {
            case ScanSetup :
                {
                    //если сканер не активен - выйдем
                    if (!m_RobotMotion->isConnected()) throw ScanError::NoConnection;
                    if (!m_RobotMotion->isReady()) throw ScanError::NoConnection;
                    //устаановилеаем стостяниее режима
                    m_ScanState = StartHoming;
                    //ошибка процесса сканирования
                    m_ScanErrorState = NoError;
                    m_ScanLineDir = false;
                    m_ScanCurrLine = -1;
                    QTimer::singleShot(0, this, SLOT(onScanProcess()));
                }
                break;
            case StartHoming :
                {
                    //if (!m_RobotMotion->moveHome(m_ScanSpeed)) throw HomeErrror;
                    if (m_RobotMotion->moveHome(m_ScanSpeed))
                    {
                        //заупскаем ождиние выхода в 0
                        m_ScanState = WaitHoming;
                        qDebug() << "waitng homeg";
                    }
                    else {
                        //сразу начинаем сканирвоание
                        m_ScanState = ScanWaitNextLine;
                        qDebug() << "wait line";
                        QTimer::singleShot(0, this, SLOT(onScanProcess()));
                    }
                    emit scanState(m_ScanFlag, m_ScanState);
                }
                break;
            case WaitHoming :
                {
                    const DecartPoint &cur = m_RobotMotion->GetCurrentXYZ();
                    DecartPoint targ = cur;
                    targ.setY(m_RobotMotion->HomeXYOffset); targ.setZ(m_RobotMotion->HomeZOffset);
                    //если стоим в нужной точке
                    if (DecartPoint::equals(cur, targ, 1.0f)) {
                        //заупскаем ождиние выхода на нчало линии сканирования
                        m_ScanState = ScanWaitNextLine;
                        qDebug() << " waiwed ";
                        QTimer::singleShot(0, this, SLOT(onScanProcess()));
                    }
                    //повторрим запрос позже
                    else QTimer::singleShot(10, this, SLOT(onScanProcess()));
                    emit scanState(m_ScanFlag, m_ScanState);
                }
                break;
            //запсиь линии скана в напрввлении вперед/назад
            case ScanLineForward :
                if (m_ScanLineDir)
                {
                    //прохдомся по точка траектории
                    bool cmd_created = false;
                    while (scanIter.hasNext() && !cmd_created) {
                        DecartPoint target = scanIter.next();
                        //qDebug() << " x " << target.x() << " y " << target.y() << " z " << target.z() << " a " << target.a();
                        //перемещаем робота в точку
                        if (!m_RobotMotion->appendTrackPoint(target, m_ScanSpeed))  {
                            //если точку добавить не удалось - команда сформирована - ждем подтвержения с последубщим вызом слота
                            //cсдвинем итератор назад
                            scanIter.previous();
                            //поднимем флаг сфоримрованной команжы
                            cmd_created = true;
                        }
                    }
                    //если команда не сфомриована - вышли поскльку точки знакчились
                    if (!cmd_created && !scanIter.hasNext()) {
                        m_RobotMotion->sendTrackPoint();
                        m_ScanState = ScanWaitLineForward ;
                        qDebug() << "wait edning";
                    }
                }
                break;
            case ScanWaitLineForward :
                if (m_ScanLineDir)
                {
                    const DecartPoint &cur_pt = m_RobotMotion->GetCurrentXYZ();
                    const DecartPoint &target = m_ScanLine.last();
                    if (DecartPoint::equals(cur_pt, target, 0.5f))
                    {
                        //заупскаем ождиние выхода на нчало линии сканирования
                        m_ScanState = ScanWaitNextLine;
                        qDebug() << " NEw Line ";
                        QTimer::singleShot(0, this, SLOT(onScanProcess()));
                    }
                    //повторрим запрос позже
                    else {
                        qDebug() << " chek line " << cur_pt.y() << " z " << cur_pt.z();
                        qDebug() << " tline " << target.y() << " z " << target.z();
                        QTimer::singleShot(10, this, SLOT(onScanProcess()));
                        emit scanState(m_ScanFlag, m_ScanState);
                    }
                }
                break;
            case ScanLineReverse :
                if (!m_ScanLineDir)
                {
                    //прохдомся по точка траектории
                    bool cmd_created = false;
                    while (scanIter.hasPrevious() && !cmd_created) {
                        DecartPoint target = scanIter.previous();
                        //qDebug() << " x " << target.x() << " y " << target.y() << " z " << target.z() << " a " << target.a();
                        //перемещаем робота в точку
                        if (!m_RobotMotion->appendTrackPoint(target, m_ScanSpeed))  {
                            //если точку добавить не удалось - команда сформирована - ждем подтвержения с последубщим вызом слота
                            //cсдвинем итератор назад
                            scanIter.next();
                            //поднимем флаг сфоримрованной команжы
                            cmd_created = true;
                        }
                    }
                    //если команда не сфомриована - вышли поскльку точки знакчились
                    if (!cmd_created) {
                        m_RobotMotion->sendTrackPoint();
                        m_ScanState = ScanWaitLineReverse;
                        qDebug() << "to Next Linere Rev";
                    }
                }
                break;
            case ScanWaitLineReverse :
                if (!m_ScanLineDir)
                {
                    const DecartPoint &cur_pt = m_RobotMotion->GetCurrentXYZ();
                    const DecartPoint &target = m_ScanLine.first();
                    if (DecartPoint::equals(cur_pt, target, 0.5f))
                    {
                        //заупскаем ождиние выхода на нчало линии сканирования
                        m_ScanState = ScanWaitNextLine;
                        qDebug() << " NEw Line ";
                        QTimer::singleShot(0, this, SLOT(onScanProcess()));
                    }
                    //повторрим запрос позже
                    else {
                        QTimer::singleShot(10, this, SLOT(onScanProcess()));
                        emit scanState(m_ScanFlag, m_ScanState);
                    }
                }
                break;
            //перемещение сканера в точку сканирвоаничя следующей линии на слеудющую линию
            case ScanWaitNextLine :
                {
                    qDebug() << "new line";
                    //зесдь всегда считаем что вышли на новую линию сканирвоания
                    //увлеичиаем чсило линий - меням напрвление
                    m_ScanCurrLine++;
                    if (m_ScanCurrLine > m_ScanLineAmout - 1) {
                        m_ScanFlag =false;
                        qDebug() << "cline " << m_ScanCurrLine << " lamount " << m_ScanLineAmout;
                        scanEnding(NoError);
                    }
                    else {

                        //инвретурем направление
                        m_ScanLineDir = !m_ScanLineDir;//сбрасываем итератор
                        scanIter = QListIterator<DecartPoint>(m_ScanLine);
                        if (m_ScanLineDir) scanIter.toFront();
                        else  scanIter.toBack();

                        m_ScanState = m_ScanLineDir ? ScanLineForward : ScanLineReverse;
                        qDebug() << "statte " << m_ScanState;
                        QTimer::singleShot(0, this, SLOT(onScanProcess()));
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
    else if (!m_ScanEnable){
        scanEnding(NoError);
    }
}
//------------------------------------------------------------------------------
//заврешение сканрования
//------------------------------------------------------------------------------
void AutoScanController::scanEnding(int exit_code)
{
    if (m_ScanFlag) m_ScanFlag = false;
    //отсновим таймер ождиания
    m_WaitResonseTimer->stop();
    //отсновим двжиение
    qDebug() << "stopping";
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
    qDebug() << "scsnTIMerOut";
    if (m_ScanFlag) m_ScanFlag =false;
    scanEnding(CmdTimeOut);
}
