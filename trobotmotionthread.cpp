 #include "trobotmotionthread.h"
#include "qdebug.h"
#include <QApplication>
//---------------------------------------------------------------------------
TRobotMotionThread::TRobotMotionThread(QObject *parent, QString ip) : QThread(parent)
{
    WSADATA WSAData;
    WSAStartup(0x101,(LPWSADATA)&WSAData);

    IPAddres = ip;
    //заполняем струтуру хоста
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr((char*)IPAddres.toLatin1().data());
    serv_addr.sin_port = htons(9015);

    CurrentCmdCount = 0;
    MotionMode= MotioType::JOIUNT;
    AxisCount = 0;
}
//------------------------------------------------------------------------------
TRobotMotionThread::~TRobotMotionThread()
{
    WSACleanup();
}
//------------------------------------------------------------------------------
//команда ВКЛЮЧения /выелючения питания мотора
//------------------------------------------------------------------------------
int TRobotMotionThread::MotorOnOF(bool on, QString &status)
{
    QString cmd = "MOTOR " + QString::number(on) + ",";
    return ProcessCommand(cmd, status);
}
//------------------------------------------------------------------------------
//команда перемещания в точку
//------------------------------------------------------------------------------
int TRobotMotionThread::MovePoint(QList<float> pt , QString &status)
{
    QString cmd = "MOVE " + QString::number(MotionMode) + ",";
    foreach (float axis, pt) {
        cmd += QString::number(axis) + ",";
    }
    return ProcessCommand(cmd, status);
}
//------------------------------------------------------------------------------
//команда перемещения оси axis на шаг step
// coord_type - система координат
//------------------------------------------------------------------------------
int TRobotMotionThread::StepMove(int axis, int step, QString &status)
{
    QString cmd = "STEP " + QString::number(MotionMode) + "," + QString::number(axis) + "," + QString::number(step) + ",";
    return ProcessCommand(cmd, status);
}
//---------------------------------------------------------------------------
int TRobotMotionThread::DepartMove(int step, QString &status)
{
    QString cmd = "DEPART " +  QString::number(step) + ",";
    return ProcessCommand(cmd, status);
}
//---------------------------------------------------------------------------
int TRobotMotionThread::SetZero(QString &status)
{
    return ProcessCommand("ZERO ", status);
}
//------------------------------------------------------------------------------
int TRobotMotionThread::LinearMove(QList<TPoint> &points)
{
    QString cmd = "LINEAR ";
    foreach (TPoint pt, points) {
        QString strpt = "(";
        foreach (float axis, pt) {
            strpt += QString::number(axis) + ",";
        }
        strpt += "),";
        cmd += strpt;
    }
    qDebug() << cmd;
    QString tstus;
    return  ProcessCommand(cmd, tstus);
}
//------------------------------------------------------------------------------
//получем текущие коринаты робота
//------------------------------------------------------------------------------
void TRobotMotionThread::updatePos(QString pos)
{
    int sep_ind = pos.indexOf(";");
    QString jt_pos = pos.mid(0, sep_ind);
    QString xyz_pos = pos.mid(sep_ind + 1, pos.length() - sep_ind);


    if (AxisCount <= 0) {
        coord_jt.clear();
        coord_xyz.clear();
    }

    //парсим координаты
    int cnt = 0;
    int seek_pos_jt = 1;
    int seek_pos_xyz = 1;
    int ind_jt = jt_pos.indexOf(",", seek_pos_jt);
    int ind_xyz = xyz_pos.indexOf(",", seek_pos_xyz);
    while (ind_jt > 0 && ind_xyz > 0)
    {
        QString num_jt = jt_pos.mid(seek_pos_jt -1, ind_jt - seek_pos_jt);
        QString num_xyz = xyz_pos.mid(seek_pos_xyz -1, ind_xyz - seek_pos_xyz);

        if (AxisCount <= 0)
        {
            //добвлаем значения оси в массив координат
            coord_jt.append(num_jt.toFloat());
            coord_xyz.append(num_xyz.toFloat());
        }
        else {
            coord_jt[cnt] = num_jt.toFloat();
            coord_xyz[cnt] = num_xyz.toFloat();
        }
        seek_pos_jt = ind_jt + 2;
        seek_pos_xyz = ind_xyz + 2;

        ind_jt = jt_pos.indexOf(",", seek_pos_jt);
        ind_xyz = xyz_pos.indexOf(",", seek_pos_xyz);
        cnt++;
    }

    //coord_jt[1] -= 1807;

    //если число осей не установлено - установим
    if (AxisCount <= 0)
    {
        AxisCount = cnt;
    }

    emit UpdateSystemState();
}
//---------------------------------------------------------------------------
// Функция выполнения команды:
// задаем софрмированный пакет команды, время ожидания готовности контроллера в мс
// возращаем статус и информацию о статусе выполнения команды.
// Результат функции:
//  0 - соединение с контроллером не активно
//  1 - команда передана, ответ от контроллера получен
// -1 - превышено время time-out
// -2 - ошибка передачи команды котролдеру
// -3 - ошибка приема ответа от контроллера
//---------------------------------------------------------------------------
int TRobotMotionThread::ProcessCommand(QString cmd, QString &state)
{
    if (Active)
    {
        // займем процесс выполнения команды если он свободен
        if (MotionCommandFree) {
            MotionCommandFree = false;
        }
        else  {
            // будем ждать окончания выполнения предыдущей команды
            DWORD time_out_time = GetTickCount() + 1000;
            qDebug() << "wiantg " << cmd;
            while (1)  {
                QApplication::processEvents();
                // займем процесс выполнения команды если он освободился
                if (MotionCommandFree) {
                   MotionCommandFree = false;
                   qDebug() << "got respnse";
                   break;
                }
                // если время ожидания истекло - выйдем с ошибкой
                if (GetTickCount() > time_out_time) {
                    qDebug() << "respnse TMEOUT";
                    return -1;
                }
            }
        }

        //добвим комеду в очердь обрабытваемых команд
        MotionCmd = cmd;
        // установим флаг команды
        MotionCommand = true;
        // будем ждать окончания выполнения команды
        int qq = 0;

        qDebug() << "sengding" << MotionCmd;
        while (MotionCommand) {  QApplication::processEvents(); qq++; } ;
        // освободим процесс выполнения команды
        MotionCommandFree = true;
        // выйдем с результатом выполнения команды
        //запомним сотояние
        state = MotionCommandStatus;        
        return MotionCommandExitCode;
    }
    else return 0;
}
//------------------------------------------------------------------------------
//создаем клиентсикй соект
//------------------------------------------------------------------------------
bool TRobotMotionThread::CreateSocket()
{
    DevSock = socket(AF_INET, SOCK_STREAM, 0);
    if (DevSock == INVALID_SOCKET) {
        qDebug() << WSAGetLastError();
        return false;
    }

    // включим режим NONBLOCKING
    u_long ena = 1;
    if (ioctlsocket(DevSock, FIONBIO, &ena) == SOCKET_ERROR) {
        closesocket(DevSock);
        DevSock = INVALID_SOCKET;
        return false;
    }

    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = 0;
    sa.sin_addr.s_addr = INADDR_ANY;

    if (bind(DevSock, (sockaddr *)&sa, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        qDebug() << "bind errror";
        closesocket(DevSock);
        DevSock = INVALID_SOCKET;
        return false;
    }

    //устанваливаем соедениение с хотсом (неболкирующий сокет сразу возвращет ошибку WSAEWOULDBLOCK)
    ::connect(DevSock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
    if (WSAGetLastError() != WSAEWOULDBLOCK) {
        qDebug() << "bock error";
        closesocket(DevSock);
        DevSock = INVALID_SOCKET;
        return false;
    }
}
//------------------------------------------------------------------------------
//пытаемся утсановить tcp соеднинение
//------------------------------------------------------------------------------
bool TRobotMotionThread::WaitConnection()
{

    fd_set write_set;
    fd_set error_set;
    FD_ZERO(&write_set);
    FD_ZERO(&error_set);

    FD_SET(DevSock, &write_set);
    FD_SET(DevSock, &error_set);

    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10;


    if (select(1, 0, &write_set, &error_set, &tv) == SOCKET_ERROR) {
        closesocket(DevSock);
        DevSock = INVALID_SOCKET;
        return false;
    }

    // если в сокете ошибка, значит соединение не получилось
    if (FD_ISSET(DevSock, &error_set)) {
        closesocket(DevSock);
        DevSock = INVALID_SOCKET;
        return false;
    }

    //если в соект можем писать - значит соедниение утсановлено
    return FD_ISSET(DevSock, &write_set);
}
//------------------------------------------------------------------------------
//проверим наличеие данных в tcp фрейме
//------------------------------------------------------------------------------
bool TRobotMotionThread::WaitData()
{
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1;
    // ждем данные от сервера
    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(DevSock, &read_set);
    if (select(1, &read_set, 0, 0, &tv) != SOCKET_ERROR) {
        return FD_ISSET(DevSock, &read_set) != 0;
    }
    return false;
}
//------------------------------------------------------------------------------
void TRobotMotionThread::run()
{
    bool wait_data = false;
    const int state_delay = 500;
    uint32_t state_time = GetTickCount() + state_delay;

    Terminate = false;
    Active = false;
    //int vsl = 1;

    uint32_t cmd_time_counter = 0;
    int coord_cnt = 0;

    QString coord_com = " COORD";

    while (!Terminate)
    {
        //создаем и бнидм сокет прослушивания
        if (DevSock == INVALID_SOCKET)
        {
            Active = false;
            CreateSocket();
            //qDebug() << "crettee";
        }
        //обраьотаем текущее активное соединение
        else if (Active)
        {
//            //если стоит флаг отпраки команды движения
//            if (MotionCommand && !MotionCommandWaitAnswer)
//            {
//                int tx_count = send(DevSock, (char*)MotionCmd.toLatin1().data(), MotionCmd.length(), 0);
//                if (tx_count == MotionCmd.length())
//                {
//                   //поднменм флаг ожидания ответа
//                   MotionCommandWaitAnswer = true;
//                   qDebug() << "sebnd;" << tx_count;
//                   cmd_time_counter = GetTickCount();
//                }
//                else {
//                    MotionCommandWaitAnswer = false;
//                    MotionCommandExitCode = MotioCmdError::ConnetionError;
//                    MotionCommand = false;

//                    closesocket(DevSock);
//                    DevSock = INVALID_SOCKET;
//                }
//            }

            //при нличии данных в буффере прочтем их
            if (WaitData())
            {
                char buf[1000];
                int rx_count = recv(DevSock, buf, 1000, 0);

                int seek_pos = 0;
                while (seek_pos < rx_count)
                {
                    QString cmd = QString::fromLatin1(&buf[seek_pos], sizeof(char)*coord_com.length());
                    if (cmd == coord_com)
                    {
                       coord_cnt++;
                       seek_pos += coord_com.length();

                       QString resp =  QString::fromLatin1(&buf[seek_pos]-5, sizeof(char)*10);
                       updatePos(resp);
                    }
                    else seek_pos++;
//                    //елси ждем команду и пришел ответ на лждаемую команду
//                    else if (MotionCommandWaitAnswer)
//                    {
//                       MotionCommand = false;
//                        MotionCommandWaitAnswer = false;

//                        //MotionCommandFree
//                        if (resp.endsWith(" OK")) {
//                            MotionCommandExitCode = MotioCmdError::NoError;
//                        }
//                        else if (resp.endsWith(" NF")) {
//                            MotionCommandExitCode = MotioCmdError::NotFound;
//                            qDebug() << "cmd not giund";
//                        }
//                        else if (resp.endsWith(" RG_ERR")) {
//                            MotionCommandExitCode = MotioCmdError::Range;
//                            qDebug() << "nfghgffbfbff";
//                        }
//                        else {
//                            MotionCommandExitCode = MotioCmdError::ConnetionError;
//                        }
//                        MotionCommandStatus = resp;
//                    }
//                    //ошибка
//                    else {
//                        qDebug() << "inlisd state ";
//                        closesocket(DevSock);
//                        DevSock = INVALID_SOCKET;
//                    }
                }
//                //получили ответ неправльиной дины
//                else{
//                    closesocket(DevSock);
//                    DevSock = INVALID_SOCKET;
//                }
            }
            else {
                //запрос координаты
                send(DevSock, "COORD ;",  sizeof("COORD ;"),1);
            }

            //сброс соедеииня
            if (DevSock == INVALID_SOCKET)
            {
                Active = false;
                qDebug() << "deisconnsede ";
                //сброс выполения коанды
                if (MotionCommandWaitAnswer) {
                    MotionCommandWaitAnswer = false;
                    MotionCommandExitCode = MotioCmdError::ConnetionError;
                    MotionCommand = false;
                }
            }


            //расчтиаем частоту получения реузльата
            if (GetTickCount() > cmd_time_counter)
            {
                //определям кол-во резульатов в секунду
                MotionFreq = coord_cnt;
                coord_cnt = 0;
                //определям количесвто оборост в секунду
                cmd_time_counter= GetTickCount() + 1000;
            }

        }
        //пытаемся подлкючться к серверу
        else if (WaitConnection())
        {   
            //сброси флаги
//            Active = true;
//            MotionCommand = false;
//            MotionCommandFree = true;
//            MotionCommandExitCode = MotioCmdError::ConnetionWait;
//            MotionCommandWaitAnswer = false;
            wait_data = false;
            coord_cnt = 0;
            qDebug() << "connnn";
        }
        // если соединения нет больше заданного времени, удалим сокет
        else  if (GetTickCount() > 15000)
        {
            //qDebug() << "conn_timemout";
            closesocket(DevSock);
            DevSock = INVALID_SOCKET;
        }
    }

    exit(0);
}
