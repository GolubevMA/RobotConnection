#include "robotmotion.h"
#include "QTimer"
#include <QFile>
//---------------------------------------------------------------------------
RobotMotion::RobotMotion(QObject *parent)
    : QObject(parent)
{
    //создаем объект сокета
    m_WorkSocket = new QTcpSocket(this);
    //создаем таймер таймута ответа
    m_timerAnsTimeout = new QTimer(this);
    //создаем таймер таймута отправки
    m_timerCmdTimeout = new QTimer(this);

    //создаем и стартуем отдельный поток обработчик
    mThread = new QThread(); mThread->start();
    //переносим этот объект в новый поток
    this->moveToThread(mThread);

    m_KinTaskSolv = KinTaskSolver();
    //m_KinTaskSolv.loadGeometry();
    m_CoordDecart.setType(DecartPoint::EulerAngles);

    //connect(m_WorkSocket, SIGNAL(aboutToClose()), this, SLOT(slotSocketClose()));
    connect(m_WorkSocket, SIGNAL(readyRead()), this, SLOT(checkResponse()));
    connect(m_timerAnsTimeout, SIGNAL(timeout()), this, SLOT(timerAnsTimeout()));
    connect(m_timerCmdTimeout, SIGNAL(timeout()), this, SLOT(writeCommand()));
    connect(m_WorkSocket, SIGNAL(disconnected()), this, SLOT(Disconnect()));

    m_waitStatus = STATE_NO_WAIT_DATA;
    m_AutoMode = false; m_AutoModeWait = false; m_AutoModeAck = true;
    m_MotionProgramm = false;
    m_queueWriteSocket.clear();
    m_wait_cmd = "";

    //очищам буффер примеа
    memset(RxBuffer, 0, sizeof(RxBuffer));
}
//---------------------------------------------------------------------------
RobotMotion::~RobotMotion()
{
    m_timerCmdTimeout->stop();
    delete m_timerCmdTimeout;

    closeConnection();
    mThread->exit();
    mThread->wait();
    delete mThread;
}
//---------------------------------------------------------------------------
//проверка ддостижимтоси точки
//---------------------------------------------------------------------------
int RobotMotion::checkPtIsValid(DecartPoint &pt)
{
    JTPoint jpt;
    return m_KinTaskSolv.solveOZK(pt, jpt);
}
//---------------------------------------------------------------------------
//перемещение на шаг в углах осей
//---------------------------------------------------------------------------
//void RobotMotion::StepMoveJT(int axis, int step, int speed)
//{
//    qDebug() << "speed " << speed;
//    QString cmd = "STEP "+QString::number(speed) + "," + QString::number(axis) + "," + QString::number(step) + "," + ";";
//    sendCmdEvent(cmd);
//}
//---------------------------------------------------------------------------
//пермещение на шаг в базисе XYZ
//---------------------------------------------------------------------------
//void RobotMotion::StepMoveXYZ(int axis, int step, int speed)
//{
    //QString cmd = "STEP "+QString::number(speed)+",2," + QString::number(axis) + "," + QString::number(step) + ",";
    //sendCmdEvent(cmd);
//}
//---------------------------------------------------------------------------
//пермещение в точку в угалх осей
//---------------------------------------------------------------------------
void RobotMotion::MovePointJT(JTPoint point, int speed)
{
    QString cmd = "MOVE "+QString::number(speed)+",";
    for (int i = 0; i < point.size(); i++) {
        cmd += QString::number(point[i], 'f',1) + ",";
    }
    cmd += ";";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//перемещение в точку (в базисе XYZ)
//---------------------------------------------------------------------------
int RobotMotion::MovePointXYZ(DecartPoint point,  int speed)
{
    JTPoint jpt;
    int res = m_KinTaskSolv.solveOZK(point, jpt);
    if (res > 0) MovePointJT(jpt, speed);
    qDebug() << "res";
    return  res;
}
//---------------------------------------------------------------------------
void RobotMotion::SetZero()
{
    sendCmdEvent("ZERO ;");
}
//---------------------------------------------------------------------------
//запуск и остановка режима птосрения траектории
//---------------------------------------------------------------------------
void RobotMotion::StartAutoMode(int speed)
{
    if (!m_AutoMode)
    {
        QString cmd ="JTLINE "+QString::number(speed)+",;";
        sendCmdEvent(cmd);
    }
}
//---------------------------------------------------------------------------
void RobotMotion::StopAutoMdoe()
{
    if (m_AutoMode)
    {
        QString cmd ="JTEND ;";        
        sendCmdEvent(cmd);
    }
}
//---------------------------------------------------------------------------
//формуруем команду, вычитываея точки из списка
//---------------------------------------------------------------------------
void RobotMotion::UpdateTrackAutoMode(QQueue<DecartPoint> &points)
{
    if (points.isEmpty()) return;

    QString cmd = "JCOORD ";

    //проходмся по точкам треактории
    while (!points.isEmpty())
    {
        DecartPoint pt = points.dequeue();
        //текущая точка
        QString cur_pt = "(";
        for (int i =0; i < pt.size(); i++) {
            cur_pt.append(QString::number(pt[i])+ ",");
        }
        cur_pt += "),";
        //добалвяем точки до тех пор, пока размер команды не превысит максимальный
        if (cur_pt.size() + cmd.size() >= MAX_CMD_SIZE-1)  {
            cmd += ";";
            qDebug() << "sending " << cmd;
            sendCmdEvent(cmd);
            return;
        }
        else cmd += cur_pt;
    }
    if (!cmd.isEmpty() && (cmd.compare("JCOORD ") != 0)) {
        qDebug() << "sending " << cmd;
        cmd += ";";
        sendCmdEvent(cmd);
    }
}
//---------------------------------------------------------------------------
//парсинг траектории
//---------------------------------------------------------------------------
void RobotMotion::ParseTrackJT(QList<JTPoint> &points, int speed)
{
    QString cmd ="JTLINE "+QString::number(speed)+",;";
    sendCmdEvent(cmd);

    cmd ="JCOORD ";
    foreach (JTPoint pt, points)
    {
        if (!pt.size()) qDebug() << "got empty string";
        //текущая точка
        QString cur_pt = "(";
        for (int i =0; i < pt.size(); i++) {
            cur_pt.append(QString::number(pt[i])+ ",");
        }
        cur_pt += "),";
        //отпрака по частям
        if (cur_pt.size() + cmd.size() >= MAX_CMD_SIZE-1)
        {
            cmd += ";";
            qDebug() << "sending " << cmd;
            sendCmdEvent(cmd);
            cmd = "JCOORD ";
        }
        else cmd += cur_pt;
    }
    if (!cmd.isEmpty() && (cmd.compare("JCOORD ") != 0)) {
        qDebug() << "sending " << cmd;
        cmd += ";";
        sendCmdEvent(cmd);
    }
    sendCmdEvent("JTEND ;");
}
//---------------------------------------------------------------------------
int RobotMotion::ParseTrackXyz(QList<DecartPoint> points, int speed)
{
    //форимурем массив точек
    QList<JTPoint> jt_points;
    jt_points.clear();
    int res = 1;
    foreach (DecartPoint pt, points) {
        JTPoint jpt;
        res = m_KinTaskSolv.solveOZK(pt, jpt);
        if (!res) return  res;
        jt_points.append(jpt);
    }
    ParseTrackJT(jt_points, speed);
    return res;
}
//---------------------------------------------------------------------------
bool RobotMotion::isConnected()
{
    return  m_WorkSocket->isOpen();
}
//---------------------------------------------------------------------------
//вызвываем слот создания сокета в потоке - обрабочткие
//---------------------------------------------------------------------------
bool RobotMotion::createConnection(QString ip, int port)
{
    m_HostIp = ip;
    m_HostPort = port;
    //m_KinTaskSolv.loadGeometry();

    m_mutexObj.lock();

    //межптотчный вызов
    QTimer::singleShot(0, this, SLOT(slotSocketOpen()));

    m_conditionMutex.lock();
    //блокируем основой поток пока поток обработчик не откроет порт
    // или пока не срабоатет таймер
    m_waitSockeSlot.wait(&m_conditionMutex, TIMEOUT_OPEN_CLOSE);
    m_conditionMutex.unlock();

    m_mutexObj.unlock();

    return m_WorkSocket->isOpen();
}
//---------------------------------------------------------------------------
//закрытие сокето из основного птока
//---------------------------------------------------------------------------
void RobotMotion::closeConnection()
{
    m_mutexObj.lock();

    //межптотчный вызов
    QTimer::singleShot(0, this, SLOT(slotSocketСlose()));

    m_conditionMutex.lock();
    //блокируем основой поток пока поток обработчик не откроет порт
    // или пока не срабоатет таймер
    m_waitSockeSlot.wait(&m_conditionMutex, TIMEOUT_OPEN_CLOSE);
    m_conditionMutex.unlock();

    m_mutexObj.unlock();
}
//---------------------------------------------------------------------------
//метод добавлеят команлду в очердь и осущемтвеляет межпоотоный вызов
// функции отправки данных по udp
//---------------------------------------------------------------------------
void RobotMotion::sendCmdEvent(QString cmd)
{
    static uint16_t cmd_counter = 0;
    //добавлям команду в очередь (так как метоы класса очреди так же вызыываюся
    // дргуоим пототк необходимо накинуть мьютекс)
    m_mutexObj.lock();
    if (m_queueWriteSocket.size() < MAX_SOCKET_QUEUE_SIZE) {
        //добавим идентификатор к команде
        int wr_pos = cmd.lastIndexOf(";")+1;
        if (wr_pos > 0) {
            cmd += QString::number(cmd_counter++);
        }
        qDebug() << "cmd " << cmd;
        m_queueWriteSocket.append(cmd);
    }
    m_mutexObj.unlock();
    //межпоотчный вызов (через 0 милискеуд)
    // в event_Loop потка данного обьект постопуит обрабочтки фукцнии
    //загрузки данных во фреймбуффер сокета
    //QTimer::singleShot(0, this, SLOT(writeCommand()));
}
//---------------------------------------------------------------------------
//бидним сокет в слоте в потоке
//---------------------------------------------------------------------------
void RobotMotion::slotSocketOpen()
{
    //биднлим соект на локал хост
    if (m_WorkSocket->open(QIODevice::ReadWrite))
    {
        qDebug() << "opened";
        if (m_WorkSocket->bind())
        {
            qDebug() << "bingend";
            //вызывваем блокирующий методо ожмания утсвик соедниния
            m_WorkSocket->connectToHost(m_HostIp, m_HostPort);
            if (m_WorkSocket->waitForConnected(500)) {
                qDebug() << "connctede";
                //активурем таймер отправки
                m_timerCmdTimeout->start(TIMEOUT_COORD);
                m_StopMotionProg = false;
                m_MotionProgramm = false;
                m_AutoMode= false;
                m_AutoModeWait = false;
                m_AutoModeAck = false;
            }
            else {
                qDebug() << "conn error" << m_WorkSocket->error();
                m_WorkSocket->close();
            }
        }
        else {
            qDebug() << "bind_erroro";
            m_WorkSocket->close();
        }
    }
    else {
        qDebug() << "openerror";
    }

    //деблокируем основной поток, ожидабщий содания сокета
    m_waitSockeSlot.wakeAll();
}
//---------------------------------------------------------------------------
//закрываем сокет в слоет в потоке
//---------------------------------------------------------------------------
void RobotMotion::slotSocketClose()
{
    //биднлим соект на локал хост
    if (m_WorkSocket->isOpen())
    {
        m_WorkSocket->close();
        //сбросим буффрепримеа
        memset(RxBuffer, 0, sizeof(RxBuffer));
        qDebug() << "closed";
    }
    else {
        qDebug() << "a;redy close";
    }

    //деблокируем основной поток, ожидабщий содания сокета
    m_waitSockeSlot.wakeAll();
}
//---------------------------------------------------------------------------
// запись комнды во фреймбуффер udp (функция вызывается с помщью сгбытия отложенного такймера)
// обрабочтик соытия таймера реализуется в потоке eventLoopa (в потоке данного обьекта)
// тайой спосб позволяет осуществить межпооточный вызов данной функции
// из пубдицчных метоло класса (исполнямых в основном потоке)
//---------------------------------------------------------------------------
void RobotMotion::writeCommand()
{
//    //есть команда ответ на которую еще не получен
//    // или выполение команды двжиения еще не закночилось
//    if (m_waitStatus == STATE_WAIT_ANS && !MotionProgramm) {
//        //повторим запрос немного позже
//        QTimer::singleShot(5, this, SLOT(writeCommand()));
//        return;
//    }
    try {
        // если выполение команды двжиения еще не закночилось
        //первем команду
        if (m_MotionProgramm && m_StopMotionProg) throw m_CmdStop;
        else if (!m_queueWriteSocket.isEmpty() && m_waitStatus != STATE_WAIT_ANS)
        {
            //отправим команду
            m_mutexObj.lock();
            QString cmd = m_queueWriteSocket.dequeue();
            char buf[256];
            memset(buf,0, sizeof(buf));
            memcpy(buf,cmd.toUtf8(), cmd.size());
            m_WorkSocket->write(buf, sizeof(buf));
            m_mutexObj.unlock();
            //запомниаем на какую команул ждем ответ
            m_wait_cmd = cmd;
            //активерум таймер оканчания ожижаения ответа
            m_timerAnsTimeout->start(TIMEOUT_ANS_ROBOT);
            m_waitStatus = STATE_WAIT_ANS;
        }
        else throw m_CmdState;
    }
    catch (QString cmd)
    {
        //отправи запрос координаты
        m_mutexObj.lock();
        char buf[256];
        memset(buf,0, sizeof(buf));
        memcpy(buf, cmd.toUtf8(), cmd.size());
        m_WorkSocket->write(buf, sizeof(buf));
        m_mutexObj.unlock();
    }
}
//---------------------------------------------------------------------------
// прерывание исполняемой команды
//---------------------------------------------------------------------------
void RobotMotion::breakCommand()
{
    //есть команда ответ на которую еще не получен
    if (m_waitStatus != STATE_WAIT_ANS)  return;

    //отправим команду остановки
    QString cmd = "BREAK";

    m_mutexObj.lock();
    m_WorkSocket->write(cmd.toUtf8(), sizeof(cmd.size()));
    m_mutexObj.unlock();
}
//---------------------------------------------------------------------------
//проверка ответа отклиента
//---------------------------------------------------------------------------
void RobotMotion::checkResponse()
{
    static int cmd_count = 0;
    static long timer =0;

    //при нличии данных в буффере прочтем их
    int rx_count = m_WorkSocket->readLine(RxBuffer, sizeof(RxBuffer));
    if (rx_count > 0)
    {
        while (rx_count > 0)
        {
            //парсим сторку
            QString resp =  QString(RxBuffer);
            //обработаем получение стаутса
            if (resp.endsWith(m_status_ident))
            {
                resp.remove(m_status_ident);
                QStringList coords = resp.split(";");
                if (coords.size() < 4) {
                    qDebug() << "; count error";
                    return;
                }
                QString jt_pos = coords[0];
                //QString xyz_pos = coords[1];
                //парсим координаты
                QStringList jt_nums = jt_pos.split(",");
                //QStringList xyz_nums = xyz_pos.split(",");
                //if (jt_nums.size() != ) return;
                for (int i = 0; i < jt_nums.size(); i++) {
                    //кооринаты jt
                    m_CoordJT[i] = jt_nums[i].toFloat();
                }
                //парсим флаг выполения и статус выполняемой команды
                m_MotionProgramm = coords[1].toInt();
                //парсим флаг автоматического движения по траектории
                m_AutoMode = coords[3].toInt();
                //читаем идентификаторо команды
                int recv_ident = coords[4].toInt();

                //определим id текущей команды
                int wait_id = -1;
                int pos = m_wait_cmd.lastIndexOf(";") + 1;
                if (pos > 0) { 
                    QString num = m_wait_cmd.right(m_wait_cmd.length() - pos);
                    wait_id = num.toInt();
                }
                //если ждем ответ на команду
                bool ack = (m_waitStatus == STATE_WAIT_ANS) && (wait_id == recv_ident);
                if (ack)
                {
                    //в автоматическом режиме опускам флаг ожидания, чтобы можно было отпраить слеудущую команду
                    if (m_AutoMode && m_AutoModeWait) {
                        m_AutoModeWait = false;
                        //команда выполнилась успешно, если отуствующт ошибки контрлолера
                        m_AutoModeAck = true;
                        //здесь мжно излучить сигнал
                        emit autoModeEvent();
                    }
                    m_timerAnsTimeout->stop();
                    //если дождаличь отсвета обновим статус ожидания
                    m_waitStatus = STATE_NO_WAIT_DATA;
                    //здесь можно испустить сигнал получения отвтоета
                    emit transaction(false);
                }

                //считаетм текущую координату
                m_CoordDecartMat = m_KinTaskSolv.solvePZK(m_CoordJT);
                KinTaskSolver::calcDecart(m_CoordDecartMat, m_CoordDecart);

                //потаем чатоту получения координаты
                cmd_count++;
                if (GetTickCount() - timer >= 1000) {
                    //число кооритан в скеунду
                    CoordFreq = cmd_count;
                    cmd_count = 0;
                    timer = GetTickCount();
                }
            }
            rx_count = m_WorkSocket->readLine(RxBuffer, sizeof(RxBuffer));
        }
    }
    else
    {
        qDebug() << " read Error " << rx_count << " ee " << m_WorkSocket->errorString();
        //сьрасываем таймер ожидания ответа
        m_timerAnsTimeout->stop();
        emit transaction(false);
        //закроем сокет
        slotSocketClose();
    }
}
//---------------------------------------------------------------------------
bool RobotMotion::autopilotCmdEnable()
{
    //есть запрос на отрпвку команлы в авторежме
    if (m_AutoModeWait) {
        return false;
    }
    //в очержи отсальись неотправленные команды
    if(!m_queueWriteSocket.empty()) {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
//таймер ожидаения ответа на команду
//---------------------------------------------------------------------------
void RobotMotion::timerAnsTimeout()
{
    m_waitStatus = STATE_NO_WAIT_DATA;
    qDebug() << "timeout";

    //если была запршена команды в авторежиме
    if(m_AutoModeWait) {
        m_AutoModeWait = false; m_AutoModeAck = false;
    }
    m_timerAnsTimeout->stop();
    //деблокируем осной поток (если по какой то причине был заблокирован)
    m_waitSockeSlot.wakeAll();
    emit transaction(false);
}
//---------------------------------------------------------------------------
void RobotMotion::Disconnect()
{
    qDebug() << "dicsted ";
    //сбросим таймер отрпрвки
    m_timerCmdTimeout->stop();
}
