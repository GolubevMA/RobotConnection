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

    //создаем и стартуем отдельный поток обработчик
    mThread = new QThread(); mThread->start();
    //переносим этот объект в новый поток
    this->moveToThread(mThread);

    //connect(m_WorkSocket, SIGNAL(aboutToClose()), this, SLOT(slotSocketClose()));
    connect(m_WorkSocket, SIGNAL(readyRead()), this, SLOT(checkResponse()));
    connect(m_timerAnsTimeout, SIGNAL(timeout()), this, SLOT(timerAnsTimeout()));
    connect(m_WorkSocket, SIGNAL(disconnected()), this, SLOT(Disconnect()));

    m_waitStatus = STATE_NO_WAIT_DATA;
    m_MotionWait = false; m_MotionAck = true;
    MotionProgramm = false;

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
    closeConnection();
    mThread->exit();
    mThread->wait();
    delete mThread;
}
//---------------------------------------------------------------------------
//перемещение на шаг в углах осей
//---------------------------------------------------------------------------
void RobotMotion::StepMoveJT(int axis, int step)
{
    QString cmd = "STEP 1," + QString::number(axis) + "," + QString::number(step) + ",";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//пермещение на шаг в базисе XYZ
//---------------------------------------------------------------------------
void RobotMotion::StepMoveXYZ(int axis, int step)
{
    QString cmd = "STEP 2," + QString::number(axis) + "," + QString::number(step) + ",";
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//пермещение в точку в угалх осей
//---------------------------------------------------------------------------
void RobotMotion::MovePointJT(JTPoint point)
{
    QString cmd = "MOVE 1,";
    foreach (float axis, point) {
        cmd += QString::number(axis) + ",";
    }
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//перемещение в точку (в базисе XYZ)
//---------------------------------------------------------------------------
void RobotMotion::MovePointXYZ(QVector3D xyz, EulerAngles oat)
{
    QString cmd = "MOVE 2,";
    for (int i =0; i < 3; i++)
    {
        cmd += QString::number(xyz[i], 'f',1) + ",";
        cmd += QString::number(oat[i],'f',1) + ",";
    }
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
void RobotMotion::MovePointXYZ(QVector3D xyz)
{
    QString cmd = "MOVE 2,";
    for (int i =0; i < 3; i++)
    {
        cmd += QString::number(xyz[i], 'f',1) + ",";
        cmd += QString::number(m_EulerAngles[i],'f',1) + ",";
    }
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
//премещение на раастние от точик
//---------------------------------------------------------------------------
void RobotMotion::DepartMove(int step)
{

}
//---------------------------------------------------------------------------
void RobotMotion::SetZero()
{
    sendCmdEvent("ZERO");
}
//---------------------------------------------------------------------------
//линиеное пермещением по указанным точкам
//---------------------------------------------------------------------------
void RobotMotion::LinearMove(QList<JTPoint> &points)
{
    QString cmd = "LINEAR ";
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
void RobotMotion::LinearMove(QList<QVector3D> &points_xyz, QList<EulerAngles>  &points_oat)
{
    QString cmd = "LINEAR ";
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
    qDebug() << cmd;
    sendCmdEvent(cmd);
}
//---------------------------------------------------------------------------
void RobotMotion::LinearMove(QList<QVector3D> &points_xyz)
{
    QString cmd = "LINEAR ";
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
    QTimer::singleShot(0, this, SLOT(writeCommand()));

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
    //есть команда ответ на которую еще не получен
    // или выполение команды двжиения еще не закночилось
    if (m_waitStatus == STATE_WAIT_ANS && !MotionProgramm) {
        //повторим запрос немного позже
        QTimer::singleShot(5, this, SLOT(writeCommand()));
        return;
    }

    // отправим первую команду в очереди
    m_mutexObj.lock();
    QString cmd = m_queueWriteSocket.dequeue();
    m_WorkSocket->write(cmd.toUtf8(), cmd.size());
    m_mutexObj.unlock();

    //запомниаем на какую команул ждем ответ
    //m_wait_ident = cmd.ident;
    m_wait_cmd = cmd;
    qDebug() << "cmd " << cmd;

    //активерум таймер оканчания ожижаения ответа
    m_timerAnsTimeout->start(TIMEOUT_ANS_ROBOT);
    m_waitStatus = STATE_WAIT_ANS;
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

    //здесь можно испосукать сигнал измения координаты
    emit coordChanged();
}
//---------------------------------------------------------------------------
void RobotMotion::Disconnect()
{
    qDebug() << "dicsted ";
}
//---------------------------------------------------------------------------
