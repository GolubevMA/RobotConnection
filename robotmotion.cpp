#include "robotmotion.h"
#include "QTimer"
//---------------------------------------------------------------------------
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

    //connect(m_WorkSocket, SIGNAL(aboutToClose()), this, SLOT(slotSocketClose()));
    connect(m_WorkSocket, SIGNAL(readyRead()), this, SLOT(checkResponse()));
    connect(m_timerAnsTimeout, SIGNAL(timeout()), this, SLOT(timerAnsTimeout()));
    connect(m_timerCmdTimeout, SIGNAL(timeout()), this, SLOT(writeCommand()));
    connect(m_WorkSocket, SIGNAL(disconnected()), this, SLOT(Disconnect()));

    m_waitStatus = STATE_NO_WAIT_DATA;
    m_MotionWait = false; m_MotionAck = true;
    MotionProgramm = false;
    m_queueWriteSocket.clear();

    //очищам буффер примеа
    memset(RxBuffer, 0, sizeof(RxBuffer));

    m_CoordJT.clear();
    for (int i =0; i < MaxAxisCount; i++){
        m_CoordJT.append(0);
    }
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
//перемещение на шаг в углах осей
//---------------------------------------------------------------------------
void RobotMotion::StepMoveJT(int axis, int step, int speed)
{
    qDebug() << "speed " << speed;
    QString cmd = "STEP "+QString::number(speed)+",1," + QString::number(axis) + "," + QString::number(step) + "," + ";";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//пермещение на шаг в базисе XYZ
//---------------------------------------------------------------------------
void RobotMotion::StepMoveXYZ(int axis, int step, int speed)
{
    QString cmd = "STEP "+QString::number(speed)+",2," + QString::number(axis) + "," + QString::number(step) + ",";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//пермещение в точку в угалх осей
//---------------------------------------------------------------------------
void RobotMotion::MovePointJT(JTPoint point, int speed)
{
    QString cmd = "MOVE "+QString::number(speed)+",1,";
    for (int i = 0; i < point.length(); i++) {
        cmd += QString::number(point.at(i), 'f',1) + ",";
    }
    cmd += ";";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//перемещение в точку (в базисе XYZ)
//---------------------------------------------------------------------------
void RobotMotion::MovePointXYZ(QVector3D xyz, EulerAngles oat,  int speed)
{
    QString cmd = "MOVE "+QString::number(speed)+",2,";
    for (int i =0; i < 3; i++) {
        cmd += QString::number(xyz[i], 'f',1) + ",";
    }
    for (int i =0; i < 3; i++) {
        cmd += QString::number(oat[i],'f',1) + ",";
    }
    cmd += ";";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
void RobotMotion::MovePointXYZ(QVector3D xyz, int speed)
{
    QString cmd = "MOVE "+QString::number(speed)+",2,";
    for (int i =0; i < 3; i++) {
        cmd += QString::number(xyz[i], 'f',1) + ",";
    }
    for (int i =0; i < 3; i++) {
        cmd += QString::number(m_EulerAngles[i],'f',1) + ",";
    }
    cmd += ";";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//премещение на раастние от точик
//---------------------------------------------------------------------------
void RobotMotion::DepartMove(int step)
{

}
//---------------------------------------------------------------------------
//движение по окружности
//---------------------------------------------------------------------------
void RobotMotion::ArcMove(QVector3D first_pt,  QVector3D dest_pt, int speed, int rad)
{
    first_pt = QVector3D(0, -20, 0);
    QVector3D temp_pt = QVector3D(0, 30, 50);
    first_pt = QVector3D(0, 80, 0);
    //формиурем вектор из текущих точек
    QList<QVector3D> points_xyz = {first_pt, temp_pt, dest_pt};
    //форимруем команду
    QString cmd = "ARC "+QString::number(speed)+",";
    for (int i=0; i < points_xyz.size(); i++)
    {
        //текущая точка
        QVector3D &pt_xyz = points_xyz[i];
        EulerAngles &pt_oat = m_EulerAngles;

        QString cur_pt = "(";
        for (int i = 0; i < 3; i++) {
            cur_pt += QString::number(pt_xyz[i]) + ",";
        }
        for (int i = 0; i < 3; i++) {
            cur_pt += QString::number(pt_oat[i]) + ",";
        }
        cur_pt += "),";
        cmd += cur_pt;
    }
}
//---------------------------------------------------------------------------
void RobotMotion::SetZero()
{
    sendCmdEvent("ZERO ;");
}
//---------------------------------------------------------------------------
//линиеное пермещением по указанным точкам
//---------------------------------------------------------------------------
void RobotMotion::LinearMove(QList<JTPoint> &points, int speed, int rad)
{
    QString cmd = "LINEAR "+QString::number(speed)+","+QString::number(rad)+",";
    foreach (JTPoint pt, points)
    {
        QString strpt = "(";
        foreach (float axis, pt) {
            strpt += QString::number(axis) + ",";
        }
        strpt += "),";
        cmd += strpt;
    }
    qDebug() << cmd;
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//линиеное пермещением по указанным точкам
//---------------------------------------------------------------------------
void RobotMotion::LinearMove(QList<QVector3D> &points_xyz, QList<EulerAngles>  &points_oat, int speed, int rad)
{
    QString cmd = "LINEAR "+QString::number(speed)+","+QString::number(rad)+",";
    for (int i=0; i < points_xyz.size(); i++)
    {
        //текущая точка
        QVector3D &pt_xyz = points_xyz[i];
        EulerAngles &pt_oat = points_oat[i];

        QString cur_pt = "(";
        for (int i = 0; i < 3; i++) {
            cur_pt += QString::number(pt_xyz[i]) + ",";
        }
        for (int i = 0; i < 3; i++) {
            cur_pt += QString::number(pt_oat[i]) + ",";
        }
        cur_pt += "),";
        cmd += cur_pt;
    }
    cmd += ";";
    qDebug() << cmd;
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
void RobotMotion::LinearMove(QList<QVector3D> &points_xyz, int speed, int rad)
{
    QString cmd = "LINEAR "+QString::number(speed)+","+QString::number(rad)+",";
    for (int i=0; i < points_xyz.size(); i++)
    {
        //текущая точка
        QVector3D &pt_xyz = points_xyz[i];
        EulerAngles &pt_oat = m_EulerAngles;

        QString cur_pt = "(";
        for (int i = 0; i < 3; i++) {
            cur_pt += QString::number(pt_xyz[i]) + ",";
        }
        for (int i = 0; i < 3; i++) {
            cur_pt += QString::number(pt_oat[i]) + ",";
        }
        cur_pt += "),";
        cmd += cur_pt;
    }
    cmd += ";";
    qDebug() << cmd;
    sendCmdEvent(cmd);
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
    //static int cmd_counter = m_cmd_mask;

    //добавлям команду в очередь (так как метоы класса очреди так же вызыываюся
    // дргуоим пототк необходимо накинуть мьютекс)
    m_mutexObj.lock();
    if (m_queueWriteSocket.size() < MAX_SOCKET_QUEUE_SIZE) {
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
                MotionProgramm = false;
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

        //если буффер команд пустой
        if (m_queueWriteSocket.isEmpty()) throw m_CmdCoord;
        //есть команда ответ на которую еще не получен
        if (m_waitStatus == STATE_WAIT_ANS) throw m_CmdCoord;
        // если выполение команды двжиения еще не закночилось
        //можем отправить тоьлько команду прерываения дижения
        if (MotionProgramm && m_StopMotionProg) throw m_CmdCoord;
        //прервем выполняющуюся команду
        else if (MotionProgramm && m_StopMotionProg)
        {
            m_mutexObj.lock();
            QString cmd = "STOP";
            m_WorkSocket->write(cmd.toUtf8(), cmd.size());
            m_mutexObj.unlock();
            //сбросим таймер оидания ответа
            m_timerAnsTimeout->stop();
            m_waitStatus = STATE_NO_WAIT_DATA;
            m_StopMotionProg = false;

        }
        else {
            //отправим команду
            m_mutexObj.lock();
            QString cmd = m_queueWriteSocket.dequeue();
            m_WorkSocket->write(cmd.toUtf8(), cmd.size());
            m_mutexObj.unlock();

            //запомниаем на какую команул ждем ответ
            m_wait_cmd = cmd;
            qDebug() << "cmd " << cmd;

            //активерум таймер оканчания ожижаения ответа
            m_timerAnsTimeout->start(TIMEOUT_ANS_ROBOT);
            m_waitStatus = STATE_WAIT_ANS;
        }
    }
    catch (QString cmd)
    {
        //отправи запрос координаты
        m_mutexObj.lock();
        m_WorkSocket->write(cmd.toUtf8(), cmd.size());
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
    //при нличии данных в буффере прочтем их
    int rx_count = m_WorkSocket->readLine(RxBuffer, sizeof(RxBuffer));
    if (rx_count > 0)
    {
        while (rx_count > 0)
        {
            //парсим сторку
            QString resp =  QString(RxBuffer);
            //ответ на команду
            if  (resp.endsWith(m_cmd_ident))
            {
                //вычленияем команду
                resp.remove(m_cmd_ident);
                QString state = resp.right(resp.indexOf(" ")-1);
                resp.remove(state);

                //если дождались отвта на нужную команду
                bool ack = m_waitStatus == STATE_WAIT_ANS && resp == m_wait_cmd;
                if (ack)
                {
                    qDebug() << "accepted " << state;
                    //если дождаличь отсвета обновим статус ожидания
                    m_waitStatus = STATE_NO_WAIT_DATA;

                    //если была запршена команды а вторежиме
                    if(m_MotionWait) {
                        m_MotionWait= false; m_MotionAck= true;
                        //emit steerEvent();
                    }
                    m_timerAnsTimeout->stop();
                    m_waitStatus = STATE_NO_WAIT_DATA;
                    //здесь можно испустить сигнал получения отвтоета
                    emit transaction(false);
                }
            }
            else if (resp.endsWith(m_coord_ident)) {
                //парсим координату
                parseResponse(resp);
            }
            rx_count = m_WorkSocket->readLine(RxBuffer, sizeof(RxBuffer));
        }
    }
    else
    {
        qDebug() << " read Error " << rx_count << " ee " << m_WorkSocket->errorString();
        //если была запршена команды а вторежиме
        if (m_MotionWait)
        {
            m_MotionWait = false; m_MotionAck = false;
            emit steerEvent();
        }
        //сьрасываем таймер ожидания ответа
        m_timerAnsTimeout->stop();
        emit transaction(false);
        //закроем сокет
        slotSocketClose();
    }
}
//---------------------------------------------------------------------------
//таймер ожидаения ответа на команду
//---------------------------------------------------------------------------
void RobotMotion::timerAnsTimeout()
{
    m_waitStatus = STATE_NO_WAIT_DATA;
    qDebug() << "timeout";

    //если была запршена команды а вторежиме
    if(m_MotionWait)
    {
        m_MotionWait = false; m_MotionAck = false;
        emit steerEvent();
    }

    m_timerAnsTimeout->stop();
    //деблокируем осной поток (если по какой то причине был заблокирован)
    m_waitSockeSlot.wakeAll();
    emit transaction(false);
}
//---------------------------------------------------------------------------
//парсим ответ
//---------------------------------------------------------------------------
void RobotMotion::parseResponse(QString &resp)
{
    //счеччики
    static int cmd_count = 0;
    static long timer =0;

    //resp.remove(m_coord_ident);
    //определим состояние
    int sep_lst = resp.length() -  resp.lastIndexOf(";");
    QString state_str = resp.right(sep_lst);
    int end_lst = state_str.indexOf(",");
    MotionProgramm = state_str.mid(2, end_lst - 2).toInt();

    resp.remove(state_str);
    int sep_ind = resp.indexOf(";");
    QString jt_pos = resp.mid(0, sep_ind);
    QString xyz_pos = resp.mid(sep_ind + 1, resp.length() - sep_ind);

    //qDebug() << "numjt" << jt_pos;

    //парсим координаты
    int axis_cnt = 0;
    int seek_pos_jt = 1;
    int seek_pos_xyz = 1;
    int ind_jt = jt_pos.indexOf(",", seek_pos_jt);
    int ind_xyz = xyz_pos.indexOf(",", seek_pos_xyz);
    while (ind_jt > 0 && ind_xyz > 0)
    {
        QString num_jt = jt_pos.mid(seek_pos_jt -1, ind_jt - seek_pos_jt);
        QString num_xyz = xyz_pos.mid(seek_pos_xyz -1, ind_xyz - seek_pos_xyz);

        //добвлаем значения оси в массив координат
        m_CoordJT[axis_cnt] = num_jt.toFloat();

        if(axis_cnt < 3) {
            m_CoordXyz[axis_cnt] = num_xyz.toFloat();
        }
        else {
            m_EulerAngles[axis_cnt-3] = num_xyz.toFloat();
        }

        seek_pos_jt = ind_jt + 2;
        seek_pos_xyz = ind_xyz + 2;

        ind_jt = jt_pos.indexOf(",", seek_pos_jt);
        ind_xyz = xyz_pos.indexOf(",", seek_pos_xyz);
        axis_cnt++;
    }

    //qDebug() << "jt " << m_CoordJT[0];

    //потаем чатоту получения координаты
    cmd_count++;
    if (GetTickCount() - timer >= 1000) {
        //число кооритан в скеунду
        CoordFreq = cmd_count;
        cmd_count = 0;
        timer = GetTickCount();
    }

    ////здесь можно испосукать сигнал измения координаты
    ///emit coordChanged();
}
//---------------------------------------------------------------------------
void RobotMotion::Disconnect()
{
    qDebug() << "dicsted ";
    //сбросим таймер отрпрвки
    m_timerCmdTimeout->stop();
}
//---------------------------------------------------------------------------
