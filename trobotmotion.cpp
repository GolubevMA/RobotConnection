    #include "trobotmotion.h"
#include "qdebug.h"
#include <QApplication>
//---------------------------------------------------------------------------
TRobotMotion::TRobotMotion(QObject *parent, QString ip, int axis_count) : QThread(parent)
{
    WSADATA WSAData;
    WSAStartup(0x101,(LPWSADATA)&WSAData);

    IPAddres = ip;
    //заполняем струтуру хоста
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr((char*)IPAddres.toLatin1().data());
    serv_addr.sin_port = htons(9015);

    CurrentCmdCount = 0;
    MotionMode= 0;
    AxisCount = axis_count;
}
//------------------------------------------------------------------------------
TRobotMotion::~TRobotMotion()
{
    WSACleanup();
}
//------------------------------------------------------------------------------
//команда ВКЛЮЧения /выелючения питания мотора
//------------------------------------------------------------------------------
int TRobotMotion::MotorOnOF(bool on, QString &status)
{
    QString cmd = "MOTOR " + QString::number(on) + ",";
    return ProcessCommand(cmd, status);
}
//------------------------------------------------------------------------------
//команда перемещания в точку
//------------------------------------------------------------------------------
int TRobotMotion::MovePoint(float *point, QString &status)
{
    QString cmd = "MOVE " + QString::number(MotionMode) + ",";
    for (int i = 0; i < AxisCount; i++) {
        cmd += QString::number(point[i]) + ",";
    }
    return ProcessCommand(cmd, status);
}
//------------------------------------------------------------------------------
//команда перемещения оси axis на шаг step
// coord_type - система координат
//------------------------------------------------------------------------------
int TRobotMotion::StepMove(int axis, int step, QString &status)
{
    QString cmd = "STEP " + QString::number(MotionMode) + "," + QString::number(axis) + "," + QString::number(step) + ",";
    return ProcessCommand(cmd, status);
}
//---------------------------------------------------------------------------
int TRobotMotion::DepartMove(int step, QString &status)
{
    QString cmd = "DEPART " +  QString::number(step) + ",";
    return ProcessCommand(cmd, status);
}
//---------------------------------------------------------------------------
int TRobotMotion::SetZero(QString &status)
{
    return ProcessCommand("ZERO ", status);
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
int TRobotMotion::ProcessCommand(QString cmd, QString &state)
{
    if (Active)
    {
        // займем процесс выполнения команды если он свободен
        if (MotionCommandFree) {
            MotionCommandFree = false;
        }
        else  {
            // будем ждать окончания выполнения предыдущей команды
            DWORD time_out_time = GetTickCount() + 500;
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
        MotionFreq = 0;
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
        qDebug() << "cngt " << MotionFreq;
        return MotionCommandExitCode;
    }
    else return 0;
}
//------------------------------------------------------------------------------
//создаем клиентсикй соект
//------------------------------------------------------------------------------
bool TRobotMotion::CreateSocket()
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
bool TRobotMotion::WaitConnection()
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
bool TRobotMotion::WaitData()
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
void TRobotMotion::run()
{
    bool wait_data = false;
    uint32_t state_time = GetTickCount() + 5000;
    Terminate = false;
    Active = false;
    //int vsl = 1;

    uint32_t cmd_time_counter;
    int coord_cnt = 0;

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
        else if (Active) {
            //если не ждем ответа - отправим команду
            if (!wait_data)
            {
                //если стоит флаг отпраки команды
                if (MotionCommand)
                {
                    qDebug() << "star sending ";
                    int tx_count = send(DevSock, (char*)MotionCmd.toLatin1().data(), MotionCmd.length(), 0);
                    if (tx_count == MotionCmd.length())
                    {
                       wait_data = true;
                       //поднменм флаг ожидания ответа
                       MotionCommandWaitAnswer = true;
                       qDebug() << "sebnd;" << tx_count;
                       cmd_time_counter = GetTickCount();
                       coord_cnt = 0;
                    }
                    else {
                        MotionCommandWaitAnswer = false;
                        MotionCommandExitCode = MotioCmdError::ConnetionError;
                        MotionCommand = false;

                        closesocket(DevSock);
                        DevSock = INVALID_SOCKET;
                    }
                }
                //по истечении времени отправим команду
                //поддрежания соедниниея
                else  if (GetTickCount() >= state_time)
                {
                    //QString cmd_pos = "GETPOS 1,";
                    QString cmd_pos = "STATUS ";
                    int tx_count = send(DevSock, (char*)cmd_pos.toLatin1().data(), cmd_pos.length(), 0);
                    if (tx_count == cmd_pos.length())
                    {
                       //поднменм флаг ожидания ответа
                        wait_data = true;
                        state_time = GetTickCount() + 5000;
                    }
                    else
                    {
                        closesocket(DevSock);
                        DevSock = INVALID_SOCKET;
                    }
                }
            }
            //при нличии данных в буффере прочтем их
            else  if (WaitData())
            {
                char buf[1000];
                int rx_count = recv(DevSock, buf, 1000, 0);
                if (rx_count > 0)
                {
                    QString resp = QString::fromLatin1(buf, rx_count);
                    //елси ждем команду
                    if (MotionCommandWaitAnswer)
                    {
                        int cnd_pos = resp.lastIndexOf(" ");
                       QString cmd = resp.left(cnd_pos);
                       //qDebug() << "commm " << cmd << " waitt " << MotionCmd;

                       //пришел ответ на лждаемую команду
                       if (cmd == MotionCmd)
                       {
                            MotionCommand = false;
                            MotionCommandWaitAnswer = false;

                            float time_sec = (GetTickCount() - cmd_time_counter) / 1000;
                            MotionFreq = coord_cnt / time_sec;

                            //MotionCommandFree
                            if (resp.endsWith(" OK")) {
                                MotionCommandExitCode = MotioCmdError::NoError;
                            }
                            else if (resp.endsWith(" NF")) {
                                MotionCommandExitCode = MotioCmdError::NotFound;
                                qDebug() << "cmd not giund";
                            }
                            else if (resp.endsWith(" RG_ERR")) {
                                MotionCommandExitCode = MotioCmdError::Range;
                            }
                            else {
                                MotionCommandExitCode = MotioCmdError::ConnetionError;
                            }
                            MotionCommandStatus = resp;
                            wait_data = false;
                        }
                        //присали координиату (сделать проверку)
                        else {
                           //qDebug()  << "udating pos" << resp;
                           coord_cnt++;
                           emit updatePos(resp);
                        }
                    }
                    else if (resp == "STATUS OK") {
                        wait_data = false;
                    }
                    //ошибка
                    else {
                        closesocket(DevSock);
                        DevSock = INVALID_SOCKET;
                        wait_data = false;
                    }
                }
                //получили ответ неправльиной дины
                else
                {
                    //сброс выполения коанды
                    if (MotionCommandWaitAnswer) {
                        MotionCommandWaitAnswer = false;
                        MotionCommandExitCode = MotioCmdError::ConnetionError;
                        MotionCommand = false;
                    }
                    closesocket(DevSock);
                    DevSock = INVALID_SOCKET;
                    wait_data = false;
                }
            }
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
        }
        //пытаемся подлкючться к серверу
        else if (WaitConnection())
        {   
            //сброси флаги
            Active = true;
            MotionCommand = false;
            MotionCommandFree = true;
            MotionCommandExitCode = MotioCmdError::ConnetionWait;
            MotionCommandWaitAnswer = false;
            //wait_data = false;
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
