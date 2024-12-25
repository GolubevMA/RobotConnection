#include "trobotmotion.h"
#include "qdebug.h"
#include <QApplication>
//---------------------------------------------------------------------------
TRobotMotion::TRobotMotion(QObject *parent, QString ip) : QThread(parent)
{
    WSADATA WSAData;
    WSAStartup(0x101,(LPWSADATA)&WSAData);

    IPAddres = ip;
    //заполняем струтуру хоста
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr((char*)IPAddres.toLatin1().data());
    serv_addr.sin_port = htons(9015);
    CurrentCmdCount = 0;
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
int TRobotMotion::MovePoint(int coord_type, QVector<int> point, QString &status)
{
    QString cmd = "MOVE " + QString::number(coord_type) + ",";
    return ProcessCommand(cmd, status);
}
//------------------------------------------------------------------------------
//команда перемещения оси axis на шаг step
// coord_type - система координат
//------------------------------------------------------------------------------
int TRobotMotion::StepMove(int coord_type, int axis, int step, QString &status)
{
    QString cmd = "STEP " + QString::number(coord_type) + "," + QString::number(axis) + "," + QString::number(step) + ",";
    return ProcessCommand(cmd, status);
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
            DWORD time_out_time = GetTickCount() + 5000;
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
                if (GetTickCount() > time_out_time) return -1;
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
                    qDebug() << "sebnd;";
                    int tx_count = send(DevSock, (char*)MotionCmd.toLatin1().data(), MotionCmd.length(), 0);
                    if (tx_count == MotionCmd.length())
                    {
                       wait_data = true;
                       //поднменм флаг ожидания ответа
                       MotionCommandWaitAnswer = true;
                    }
                        else {
                        MotionCommandWaitAnswer = false;
                        MotionCommandExitCode = -2;
                        MotionCommand = false;

                        closesocket(DevSock);
                        DevSock = INVALID_SOCKET;
                    }
                }
                //по истечении времени отправим команду
                //получения сотсояния
                else  if (GetTickCount() >= state_time)
                {
                    QString cmd_pos = "GETPOS 1,";
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
            else  if (WaitData()) {
                char buf[1000];
                int rx_count = recv(DevSock, buf, 1000, 0);
                if (rx_count > 0)
                {
                    //если запрос оканчивается на OK - команда принята
                    QString resp = QString::fromLatin1(buf, rx_count);
                    if (MotionCommandWaitAnswer)
                    {
                        MotionCommand = false;
                        MotionCommandWaitAnswer = false;

                        //MotionCommandFree
                        if (resp.endsWith(" OK")) {
                            MotionCommandExitCode = 1;
                        }
                        else if (resp.endsWith(" NF")) {
                            MotionCommandExitCode = -1;
                            qDebug() << "cmd not giund";
                        }
                        else if (resp.endsWith(" RG ERR")) {
                            MotionCommandExitCode = -3;
                        }
                        else {
                            MotionCommandExitCode = -2;
                        }
                        MotionCommandStatus= resp;
                    }
                    //присалит координату
                    else {
                        emit updatePos(resp);
                    }
                    wait_data = false;
                }
                //получили ответ неправльиной дины
                else
                {
                    //сброс выполения коанды
                    if (MotionCommandWaitAnswer) {
                        MotionCommandWaitAnswer = false;
                        MotionCommandExitCode = -2;
                        MotionCommand = false;
                    }
                    closesocket(DevSock);
                    DevSock = INVALID_SOCKET;
                }
            }
            if (DevSock == INVALID_SOCKET)
            {
                Active = false;
                qDebug() << "deisconnsede ";
                //сброс выполения коанды
                if (MotionCommandWaitAnswer) {
                    MotionCommandWaitAnswer = false;
                    MotionCommandExitCode = -2;
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
            MotionCommandExitCode = 0;
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
