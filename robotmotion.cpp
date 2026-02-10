 #include "robotmotion.h"
#include "QTimer"
#include <QFile>
//---------------------------------------------------------------------------
RobotMotion::RobotMotion(QObject *parent)
    : QObject(parent)
{
    //создаем объекы сокетов
    m_WorkSocket = new QTcpSocket(this);
    m_StateSocket = new QUdpSocket(this);

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

    HomeXYOffset = 150;
    HomeZOffset = -100;

    //connect(m_WorkSocket, SIGNAL(aboutToClose()), this, SLOT(slotSocketClose()));
    connect(m_StateSocket, SIGNAL(readyRead()), this, SLOT(checkResponse()));
    connect(m_timerAnsTimeout, SIGNAL(timeout()), this, SLOT(timerAnsTimeout()));
    connect(m_timerCmdTimeout, SIGNAL(timeout()), this, SLOT(writeUdpReqest()));
    connect(m_WorkSocket, SIGNAL(disconnected()), this, SLOT(Disconnect()));

    m_waitStatus = STATE_NO_WAIT_DATA;
    m_Active = false;
    m_ContinousModeWait = false;
    m_ContinousModeAck = false;

    m_queueWriteSocket.clear();
    m_wait_cmd = "";
    m_ContinousCommand = "JCOORD ";

    //очищам буффер примеа
    //memset(RxBuffer, 0, sizeof(RxBuffer));
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
bool RobotMotion::calcStepMove(int axis, float step, DecartPoint &res_point)
{
//    JTPoint jpt;
//    int err = m_KinTaskSolv.solveOZK(pt, jpt)
    return  true;
}
//---------------------------------------------------------------------------
//преобразование точки в строку
//---------------------------------------------------------------------------
QString RobotMotion::pointToString(JTPoint &pt, int speed)
{
    QString cur_pt = "("+QString::number(speed)+",";
    for (int i =0; i < pt.size(); i++) {
        cur_pt.append(QString::number(pt[i])+ ",");
    }
    cur_pt += "),";
    return  cur_pt;
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
bool RobotMotion::stepMoveXYZ(int axis, float step, int speed)
{
    if (axis > 0 && axis < DecartPoint::CoordCount) return false;

    //расчет целевой точки
    std::array<float, DecartPoint::CoordCount> pt = m_CoordDecart.points();
    pt[axis] += step;
    DecartPoint target; target.setPoints(pt);

    //решение ОЗК - проверка достжимаости точки
    JTPoint jt_pt;
    int res = m_KinTaskSolv.solveOZK(target, jt_pt);
    if (!res) return  false;

    QString cmd = "JCOORD ";
    cmd += pointToString(jt_pt, speed) + ";";
    sendCmdEvent(cmd);

}
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
    //пермещение вдоль оси z
    DecartPoint z_move = m_CoordDecart;
    z_move.setZ(HomeZOffset);
    //решение ОЗК - проверка достжимаости точки
    JTPoint jt_pt;
    int res = m_KinTaskSolv.solveOZK(z_move, jt_pt);
    if (res < 1) return false;
    QString cmd = "JCOORD "+pointToString(jt_pt, speed);

    //перемещение вдоль осей x y
    DecartPoint xy_move = z_move;
    xy_move.setY(HomeXYOffset);
    //решение ОЗК - проверка достжимаости точки
    res = m_KinTaskSolv.solveOZK(xy_move, jt_pt);
    if (res < 1)  {
        qDebug() << "res " << res;
        return false;
    }

    cmd += pointToString(jt_pt, speed) + ";";
    qDebug() << "cmd " << cmd;
    sendCmdEvent(cmd);
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
    for (int i =0; i < jpt.size(); i++) {
        cur_pt.append(QString::number(jpt[i])+ ",");
    }
    cur_pt += "),";
    //если при добвланеии точки команда превывшает максимлаьнй размер
    // отправим кмаонду и вернем false
    if (cur_pt.size() + m_ContinousCommand.size() >= MAX_CMD_SIZE-1)
    {
        m_ContinousCommand += ";";
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
//отправка точки
//---------------------------------------------------------------------------
int RobotMotion::sendTrackPoint()
{
    m_ContinousCommand += ";";
    sendCmdEvent(m_ContinousCommand);
    //сбросим команду
    m_ContinousCommand = "JCOORD ";
}
//---------------------------------------------------------------------------
bool RobotMotion::isConnected()
{
    return  m_WorkSocket->isOpen() && m_StateSocket->isOpen();
}
//---------------------------------------------------------------------------
//вызвываем слот создания сокета в потоке - обрабочткие
//---------------------------------------------------------------------------
bool RobotMotion::createConnection(QString ip, int port_tcp, int port_udp)
{
    m_HostIp = ip;
    m_HostPort = port_tcp;
    m_HostUdpPort = port_udp;
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
    QTimer::singleShot(0, this, SLOT(slotSocketClose()));

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
        m_queueWriteSocket.append(cmd);
    }
    m_mutexObj.unlock();
    //межпоотчный вызов (через 0 милискеуд)
    // в event_Loop потка данного обьект постопуит обрабочтки фукцнии
    //загрузки данных во фреймбуффер сокета
    QTimer::singleShot(0, this, SLOT(writeCommand()));
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
    try {
        //настройаа udp сокета
        if (!m_StateSocket->open(QIODevice::ReadWrite)) throw QString("udp openerror");
        if (!m_StateSocket->bind(QHostAddress::AnyIPv4, 8200)) throw QString("udp bind error");
        //получим порт udp киента
        m_UdpClientPort = m_StateSocket->localPort();
        //настройка tcp сокета
        if (!m_WorkSocket->open(QIODevice::ReadWrite)) throw QString("tcp openerror");
        if (!m_WorkSocket->bind()) throw QString("bind_erroro");
        //вызывваем блокирующий методо ожмания утсвик соедниния
        m_WorkSocket->connectToHost(m_HostIp, m_HostPort);
        if (!m_WorkSocket->waitForConnected(500)) throw QString("conn error");
        //активурем таймер отправки
        m_timerCmdTimeout->start(TIMEOUT_COORD);
        qDebug() << "conncteded StThr" << m_StateSocket->thread() << " ThisThr " << this->thread() << " err " << m_StateSocket->error();
    }
    catch (QString msg) {
        //зкароем все соекты
        if (m_WorkSocket->isOpen()) m_WorkSocket->close();
        if (m_StateSocket->isOpen()) m_StateSocket->close();
        qDebug() << "error " << msg;
    }

    //деблокируем основной поток, ожидабщий содания сокета
    m_waitSockeSlot.wakeAll();
}
//---------------------------------------------------------------------------
//закрываем сокет в слоет в потоке
//---------------------------------------------------------------------------
void RobotMotion::slotSocketClose()
{
    //закрваем все соекты
    if (m_WorkSocket->isOpen()) {
        m_WorkSocket->close();
        qDebug() << "tcp closed";
    }

    if (m_StateSocket->isOpen()) {
        m_StateSocket->close();
        ////сбросим буффрер приема
        //memset(RxBuffer, 0, sizeof(RxBuffer));
        qDebug() << "udp closed";
    }

    //деблокируем основной поток, ожидабщий содания сокета
    m_waitSockeSlot.wakeAll();
}
//---------------------------------------------------------------------------
//отправление команды активности клиента по таймеру
//---------------------------------------------------------------------------
void RobotMotion::writeUdpReqest()
{
    if (m_StateSocket->isOpen())
    {
        char buf[256];
        memset(buf,0, sizeof(buf));
        //фомриум команду
        QString cmd = m_CmdState + QString::number(m_UdpClientPort) + ";";
        memcpy(buf,cmd.toUtf8(), cmd.size());
        //отпраовяем запрос
        m_mutexObj.lock();
        m_StateSocket->writeDatagram(buf, sizeof(buf), QHostAddress(m_HostIp), m_HostUdpPort);
        m_mutexObj.unlock();
    }
}
//---------------------------------------------------------------------------
// запись комнды во фреймбуффер udp (функция вызывается с помщью межпточного вызова)
// обрабочтик события реализуется в потоке eventLoopa (в потоке данного обьекта)
// тайой спосб позволяет осуществить межпооточный вызов данной функции
// из пубдицчных метоло класса (исполнямых в основном потоке)
//---------------------------------------------------------------------------
void RobotMotion::writeCommand()
{
    //есть команда ответ на которую еще не получен
    // или выполение команды двжиения еще не закночилось
    if (m_waitStatus == STATE_WAIT_ANS) {
        //повторим запрос немного позже
        QTimer::singleShot(5, this, SLOT(writeCommand()));
        return;
    }
    //try {
    char buf[256];
    memset(buf,0, sizeof(buf));
    //есил есть команжы для отправки - отправим
    if (!m_queueWriteSocket.isEmpty() && m_waitStatus != STATE_WAIT_ANS)
    {
        m_mutexObj.lock();
        //отправим команду
        QString cmd = m_queueWriteSocket.dequeue();
        memcpy(buf,cmd.toUtf8(), cmd.size());
        m_WorkSocket->write(buf, sizeof(buf));
        m_mutexObj.unlock();
        //поднимаем флаг ожидания ответа на команду двжиения
        m_ContinousModeWait = true;
        //запомниаем на какую команул ждем ответ
        m_wait_cmd = cmd;
        //активерум таймер оканчания ожижаения ответа
        m_timerAnsTimeout->start(TIMEOUT_ANS_ROBOT);
        m_waitStatus = STATE_WAIT_ANS;
    }

//    else {
//        static int statei = 0;
//        //отправи запрос координаты
//        m_mutexObj.lock();
//        QString cmd = m_CmdState;
//        memcpy(buf, cmd.toUtf8(), cmd.size());
//        m_WorkSocket->write(buf, sizeof(buf));
//        m_mutexObj.unlock();
//    }
//    }
//    catch (QString cmd)
//    {
//    }
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
    static quint32 timer = 0;

    //читаем накопившивеся датаграммы
    while (m_StateSocket->hasPendingDatagrams())
    {
        QByteArray rdata;
        rdata.resize(int(m_StateSocket->pendingDatagramSize()));
        QHostAddress addr; quint16 host;
        qint64 rx_count = m_StateSocket->readDatagram(rdata.data(), rdata.size(), &addr, &host);
        //провеярм что ответе пришел от нужного серврера
        if ((addr == QHostAddress(m_HostIp)) && (host = m_UdpClientPort))
        {
            //разбираем команду
            if (rx_count > 0)
            {
                QString resp = QString::fromUtf8(rdata.constData(), int(rx_count));
                resp.remove(m_status_ident);
                QStringList coords = resp.split(";");
                if (coords.size() < 4) {
                    qDebug() << "; count error";
                    continue;
                }
                QString jt_pos = coords[0];
                //парсим координаты
                QStringList jt_nums = jt_pos.split(",");
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
                        //1qDebug() << "cmdAAck";
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
            else
            {
                qDebug() << " read Error " << rx_count << " ee " << m_StateSocket->errorString();
                //сьрасываем таймер ожидания ответа
                m_timerAnsTimeout->stop();
                //emit transaction(false);
                //закроем сокеты
                slotSocketClose();
                break;
            }
        }
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
    slotSocketClose();
    //сбросим таймер отрпрвки
    m_timerCmdTimeout->stop();
}
