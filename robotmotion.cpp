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

    m_CoordDecartMat.setToIdentity();
    std::array<float, 6> hm =  {0,70,-50,0,20,0};
    m_HomePos.setPoints(hm);

    //connect(m_WorkSocket, SIGNAL(aboutToClose()), this, SLOT(slotSocketClose()));
    connect(m_WorkSocket, SIGNAL(readyRead()), this, SLOT(checkResponse()));
    connect(m_timerAnsTimeout, SIGNAL(timeout()), this, SLOT(timerAnsTimeout()));
    connect(m_timerCmdTimeout, SIGNAL(timeout()), this, SLOT(writeCommand()));
    connect(m_WorkSocket, SIGNAL(disconnected()), this, SLOT(Disconnect()));

    m_waitStatus = STATE_NO_WAIT_DATA;
    m_Active = false;
    m_ContinousModeWait = false;
    m_ContinousModeAck = false;

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
void RobotMotion::movePointJT(JTPoint point, int speed)
{
    QString cmd = "JCOORD ";
    QString cur_pt = "("+QString::number(speed)+",";
    for (int i =0; i < point.size(); i++) {
        cur_pt.append(QString::number(point[i])+ ",");
    }
    cur_pt += "),";
    cmd += cur_pt + ";";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//перемещение в точку (в базисе XYZ)
//---------------------------------------------------------------------------
int RobotMotion::movePointXYZ(DecartPoint point,  int speed)
{
    JTPoint jpt;
    int res = m_KinTaskSolv.solveOZK(point, jpt);
    if (res > 0) movePointJT(jpt, speed);
    qDebug() << "res";
    return  res;
}
//---------------------------------------------------------------------------
//вжиение в позицию HOME в непрервыном режиме
//---------------------------------------------------------------------------
bool RobotMotion::moveHome(int speed)
{
    //выход по Z
    std::array<float, 6> p1f = {0,90,0,0,0,0};
    JTPoint p1(p1f);
    //выход по X/Y
    JTPoint p2(m_HomePos);

    QList<JTPoint> pts;
    pts.append(p1); pts.append(p2);

    QString cmd = "JCOORD ";
    foreach (JTPoint pt, pts)
    {
        QString cur_pt = "("+QString::number(speed) + ",";
        for (int i =0; i < pt.size(); i++) {
            cur_pt.append(QString::number(pt[i])+ ",");
        }
        cur_pt += "),";
        cmd += cur_pt;
    }
    cmd += ";";
    sendCmdEvent(cmd);
    return true;
}
//---------------------------------------------------------------------------
void RobotMotion::ParseTrackJT(QList<JTPoint> &points, int speed)
{
    QString cmd ="JCOORD ";
    foreach (JTPoint pt, points)
    {
        if (!pt.size()) qDebug() << "got empty string";
        //текущая точка
        QString cur_pt = "("+QString::number(speed)+",";
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
//формуруем команду, вычитываея точки из списка
//возращет true если может добавить точку в команду
//если нет - возращет false и оптравлет команду
//---------------------------------------------------------------------------
int RobotMotion::appendTrackPoint(DecartPoint pt, int speed)
{
    JTPoint jpt;
    int res =  m_KinTaskSolv.solveOZK(pt,jpt);
    if (!res) return -1;

    //текущая точка
    QString cur_pt = "(";
    cur_pt.append(QString::number(speed)+ ",");
    for (int i =0; i < pt.size(); i++) {
        cur_pt.append(QString::number(pt[i])+ ",");
    }
    cur_pt += "),";
    //если при добвланеии точки команда превывшает максимлаьнй размер
    // отправим кмаонду и вернем false
    if (cur_pt.size() + m_ContinousCommand.size() >= MAX_CMD_SIZE-1)
    {
        m_ContinousCommand += ";";
        qDebug() << "sending " << m_ContinousCommand;
        sendCmdEvent(m_ContinousCommand);
        //сбросим команду
        m_ContinousCommand = "JCOORD ";
        return 0;
    }
    else {
        m_ContinousCommand += cur_pt;
        return 1;
    }
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
    //блокируем основой поток пока поток обработчик не закроет порт
    // или пока не срабоатет таймер
    m_waitSockeSlot.wait(&m_conditionMutex, TIMEOUT_OPEN_CLOSE);
    m_conditionMutex.unlock();

    m_mutexObj.unlock();
}
//---------------------------------------------------------------------------
//метод добавлеят команлду в очердь и осущемтвеляет межпоотоный вызов
// функции отправки данных по tcp
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
//очистка очереди команд
//---------------------------------------------------------------------------
void RobotMotion::clearCmdQueue()
{
    m_mutexObj.lock();

    if (!m_queueWriteSocket.isEmpty()) {
        m_queueWriteSocket.clear();
    }

    m_mutexObj.unlock();
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
                //отправляем команду инициализации
                //initRobot();
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
        //есил есть команжы для отправки - отправим
        if (!m_queueWriteSocket.isEmpty() && m_waitStatus != STATE_WAIT_ANS)
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
//инициализация неперевыного режима
//---------------------------------------------------------------------------
void RobotMotion::initRobot()
{
    if (!m_Active)
    {
        m_ContinousModeWait = false;
        m_ContinousModeAck = false;
        //отправка команды инициализации
        sendCmdEvent("CONTIN_INIT ;");
    }
}
//---------------------------------------------------------------------------
void RobotMotion::closeRobot()
{
    if (m_Active) {
        //отправка команды инициализации
        //возжмно стоит сделать waitCondition
        sendCmdEvent("CONTIN_CLOSE ;");
    }
}
//---------------------------------------------------------------------------
//остновка выполения команды двжиения
//---------------------------------------------------------------------------
void RobotMotion::stopCommand()
{
    if (m_Active) {
        sendCmdEvent("CMD_STOP ;");
    }
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
                //парсим флаг неперрывного режима
                m_Active = coords[1].toInt();
                //читаем идентификаторо команды
                int recv_ident = coords[3].toInt();

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
                    //в неперрывном режиме опускам флаг ожидания, чтобы можно было отпраить слеудущую команду
                    if (m_ContinousModeWait)
                    {
                        m_ContinousModeWait = false;
                        //команда выполнилась успешно, если отуствующт ошибки контрлолера
                        m_ContinousModeAck = true;
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
//проверка активности сканера
//---------------------------------------------------------------------------
bool RobotMotion::isReady()
{
    return isConnected() && m_Active;
}
//---------------------------------------------------------------------------
//проверка возмжоности отправки команды в автоержиме
//---------------------------------------------------------------------------
bool RobotMotion::autoScanCmdEnable()
{
    //есть запрос на отрпвку команлы в авторежме
    if (m_ContinousModeWait) {
        return false;
    }
    //в очержи отсалась неотправленная команда
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
    if(m_ContinousModeWait) {
        m_ContinousModeWait = false; m_ContinousModeAck = false;
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
