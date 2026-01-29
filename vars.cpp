
#include "vars.h"
#include "qdebug.h"
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <QVector3D>
#include <QMatrix>
#include <QMatrix4x4>
//------------------------------------------------------------------------------
ControlSystemModel::ControlSystemModel()
{
//    rotateDirections << gp_Ax1(gp_Pnt(0,0,0), gp_Dir(0,0,1)) << gp_Ax1(gp_Pnt(100,0,360),gp_Dir(1,0,0)) << gp_Ax1(gp_Pnt(0,0,720),gp_Dir(1,0,0))
//                << gp_Ax1(gp_Pnt(0,0,720),gp_Dir(0,0,1)) <<gp_Ax1(gp_Pnt(100,0,1086),gp_Dir(1,0,0)) <<gp_Ax1(gp_Pnt(0,0,0),gp_Dir(0,0,1));
    rotateDirections.clear();
    robotShape.clear();
    Created = false;
}
//------------------------------------------------------------------------------
// модель сисьтемы контроля разделятся на подвижные детали (оси робота ) и непожвижные
//-----------------------------------------------------------------------------
void ControlSystemModel::LoadSystemModel(QString filename)
{
    //парсин STEP
    std::string fl = "J:\\test\\occt-samples-qopenglwidget-master\\occt-qopenglwidget\\RS007N-BC01.stp";
    Standard_CString fname = fl.c_str();// = (char*)filename.toLatin1().data();
    //Standard_CString fname = "J:\\test\\occt-samples-qopenglwidget-master\\occt-qopenglwidget\\RS007N-BC01.stp";
    STEPControl_Reader step_reader;

    qDebug() << fname;

    int ret  = step_reader.ReadFile(fname);
    if (ret != IFSelect_ReturnStatus::IFSelect_RetDone) return;

    //обьекты trnafer reader
    const Handle_XSControl_WorkSession & theSession = step_reader.WS();
    const Handle_XSControl_TransferReader & aReader = theSession->TransferReader();
    const Handle_Transfer_TransientProcess & tp = aReader->TransientProcess();

    IFSelect_PrintCount mode = IFSelect_PrintCount(1);
    step_reader.PrintCheckLoad(false, mode);
    Standard_Integer NbRoots = step_reader.NbRootsForTransfer();

    Standard_Integer NbTrans = step_reader.TransferRoots();
    qDebug() << "STEP roots transferred " << NbTrans;
    qDebug() << "Number of resulting shapes is " << step_reader.NbShapes();

    //выполеям преобразования обьектов step в обьекты opencacade
    step_reader.TransferRoots();
    TopoDS_Shape aShape = step_reader.OneShape();

    //точка куда смщается начало робота
    gp_Pnt pt_offset = gp_Pnt(0,-500,-300);
    gp_Trsf offset;
    offset.SetTranslation(gp_Vec(gp_Pnt(0,0,0), pt_offset));


    //фигруы подвижных осей робота
    QList<TopoDS_Shape> jt_solids;
    //остальбные фигуры модели
    QList<TopoDS_Shape> othetr_solids;

    //проходимся по всем фигурам в данном наборе
    for(TopoDS_Iterator anIt(aShape); anIt.More(); anIt.Next())
    {
        TopoDS_Shape curShape = anIt.Value();
        //TopoDS_Shape shape = TransferBRep::ShapeResult(tp, transient);
        TopAbs_ShapeEnum type = curShape.ShapeType(); 

        //твердое телло
        if(type==TopAbs_SOLID)
        {   
            //преобразовым shape в entity
            Handle(Standard_Transient) anEntity = aReader->EntityFromShapeResult(curShape, 1);
            if(!anEntity.IsNull())
            {
                //получаем entity NextAssemblyUsageOccurrence
                if (strcmp ((anEntity->DynamicType())->Name(), "StepRepr_NextAssemblyUsageOccurrence") == 0)
                {
                    Handle(StepRepr_NextAssemblyUsageOccurrence) entity = Handle(StepRepr_NextAssemblyUsageOccurrence)::DownCast(anEntity);
                    QString derailName = QString::fromLocal8Bit(entity->Name()->ToCString());

                    //если в названии детали есть номер оси - деталь является подвижной осью робота
                    if (derailName.contains(QRegExp("\\w+\\-\\w+\\_J\\d+")))
                    {
                        //добвелям элмент в списко деталей робота
                        curShape.Move(offset);
                        jt_solids << curShape;
                        qDebug() << "axis " << derailName;
                    }
                    else {
                        //добавляе в список остальных деталей
                        curShape.Move(offset);
                        othetr_solids << curShape;
                    }
                }
            }
        }
        //соствное твердое тело
        if(type == TopAbs_COMPOUND)
        {
            qDebug() <<"____COMPOUND____" ;
            for(TopoDS_Iterator anExp(curShape); anExp.More(); anExp.Next())
            {
                TopoDS_Shape curShape1 = anExp.Value();
                TopAbs_ShapeEnum type1 = curShape1.ShapeType();

                //здесть можно тоже проыерять, если явлеятся частью робота
                if (type1 == TopAbs_SOLID)
                {
                    //добавляе в список остальных деталей
                    curShape.Move(offset);
                    othetr_solids << curShape;
                }
            }
        }
    }

    //стол
    gp_Pnt pt_tab_offset = gp_Pnt(0,0,pt_offset.Z());
    gp_Trsf tab_offset;
    tab_offset.SetTranslation(gp_Vec(gp_Pnt(0,0,0), pt_tab_offset));
    TopoDS_Shape aCylc = BRepPrimAPI_MakeCylinder(100, 300).Shape();
    aCylc.Move(tab_offset);


    //фомриурем набор нормалей к плоскостям
    //отнсительно которых вращаются оси робота
    rotateDirections.clear();
    rotateDirections.append(gp_Ax1(pt_offset, gp_Dir(0,0,1)));

    for (int i = 1; i < jt_solids.length(); i++)
    {
        //пересечения текущей  детали  с предыдущей
        TopOpeBRep_ShapeIntersector inspect;
        inspect.InitIntersection(jt_solids.at(i-1), jt_solids.at(i));

        //поверхность  пересчения набо выбрасть меньшую по площаи
        TopoDS_Shape s1 = inspect.CurrentGeomShape(i == 4 ? 1 : 2);

        //перемшаем shape
        if( s1.ShapeType() == TopAbs_FACE)
        {
            TopoDS_Face face = TopoDS::Face(s1);
            //елси повернсть является послоктью
            BRepAdaptor_Surface surface = BRepAdaptor_Surface(face);
            if (surface.GetType() == GeomAbs_Plane) {
                //получаем нормаль к полсокости в точкре крепления
                gp_Ax1 normal =  surface.Plane().Axis();
                rotateDirections.append(i == 1 ? normal.Reversed() : normal);
            }
            else if (surface.GetType() == GeomAbs_Cylinder) {
                //получаем нормаль к полсокости перпендикулярной главно оси цилиндра
                gp_Ax1 normal =  surface.Cylinder().Axis();
                rotateDirections.append(i == 1 ? normal.Reversed() : normal);
            }
            else {
                qDebug()  << " invaslid surface " << i;
                return;
            }
        }
    }


    //здесь все детали стачиные shapes надо обьединиьт  в  один
    //staticShape = new AIS_Shape(othetr_solids.at(0));

    //формируем список осей
    staticShape.clear();
    Handle(AIS_Shape) robshape = new AIS_Shape(othetr_solids.at(0));
    Handle(AIS_Shape) cylcshape = new AIS_Shape(aCylc);

    staticShape.append(robshape);
    staticShape.append(cylcshape);

    //формируем список осей
    robotShape.clear();
    for(int i=0; i< jt_solids.length(); i++)
    {        
        jt_solids[i].Orientation(TopAbs_Orientation::TopAbs_FORWARD);
        Handle(AIS_Shape) anAIS_Shape = new AIS_Shape(jt_solids[i]);
        robotShape.append(anAIS_Shape);
    }

    Created = true;
}
//------------------------------------------------------------------------------
KinTaskSolver::KinTaskSolver()
{
    jt2_len = 355.0f;
    jt3_len = 375.0f;
    jt5_len = 78.0f;

    offset_x = 0;
    offset_y = 0;
    offset_z = 0;

    j1_min = -180; j1_max = 180;
    j2_min = -135; j2_max = 135;
    j3_min = -155; j3_max = 155;
    j4_min = -180; j4_max = 180;
    j5_min = -125; j5_max = 125;
    j6_min = -180; j6_max = 180;
}
//------------------------------------------------------------------------------
//KinTaskSolver::KinTaskSolver(float jt2, float jt3, float jt5)
//{
//    jt2_len = jt2;
//    jt3_len = jt3;
//    jt5_len = jt5;

//    offset_x = 0;
//    offset_y = 0;
//    offset_z = 0;

//    j1_min = -180; j1_max = 180;
//    j2_min = -135; j2_max = 135;
//    j3_min = -155; j3_max = 155;
//    j4_min = -180; j4_max = 180;
//    j5_min = -125; j5_max = 125;
//    j6_min = -180; j6_max = 180;
//}
//------------------------------------------------------------------------------
void KinTaskSolver::loadGeometry()
{
    jt2_len = 355.0f;
    jt3_len = 375.0f;
    jt5_len = 78.0f;

    j1_min = -180; j1_max = 180;
    j2_min = -135; j2_max = 135;
    j3_min = -155; j3_max = 155;
    j4_min = -180; j4_max = 180;
    j5_min = -125; j5_max = 125;
    j6_min = -180; j6_max = 180;
}
//------------------------------------------------------------------------------
//Решегие ПЗК
//------------------------------------------------------------------------------
QMatrix4x4 KinTaskSolver::solvePZK(JTPoint &pt)
{
    jt2_len = 355.f;
    jt3_len = 375.f;
    jt5_len = 78.f;

    //определение параметров Денавита-Хартенберга для каждого cустава
    QMatrix4x4 T1(
            cosf(-pt.a1rad()), 0.0f, sinf(-pt.a1rad()), 0.0f,
            sinf(-pt.a1rad()), 0.0f, -cosf(-pt.a1rad()), 0.0f,
            0.0f,  1.0f,  0.0f,  0.0f,
            0.0f,  0.0f,   0.0f,  1.0f);

    QMatrix4x4 T2(
            cosf(static_cast<float>(M_PI/2) -pt.a2rad()), -sinf(static_cast<float>(M_PI/2) -pt.a2rad()), 0.0f, jt2_len*cos(static_cast<float>(M_PI/2) -pt.a2rad()),
            sinf(static_cast<float>(M_PI/2) -pt.a2rad()), cosf(static_cast<float>(M_PI/2) -pt.a2rad()), 0.0f, jt2_len*sin(static_cast<float>(M_PI/2) -pt.a2rad()),
            0.0f,  0.0f,  1.0f,  0.0f,
            0.0f,  0.0f,   0.0f,  1.0f);

    QMatrix4x4 T3(
            cosf(pt.a3rad()+static_cast<float>(M_PI/2)), 0.0f, sinf(pt.a3rad()+static_cast<float>(M_PI/2)), 0.0f,
            sinf(pt.a3rad() + static_cast<float>(M_PI/2)), 0.0f, -cosf(pt.a3rad() + static_cast<float>(M_PI/2)), 0.0f,
            0.0f,  1.0f,  0.0f,  0.0f,
            0.0f,  0.0f,   0.0f,  1.0f);

    QMatrix4x4 T4(
            cosf(pt.a4rad()), 0.0f, -sinf(pt.a4rad()), 0.0f,
            sinf(pt.a4rad()), 0.0f, cosf(pt.a4rad()), 0.0f,
            0.0f,  -1.0f,  0.0f,  jt3_len,
            0.0f,  0.0f,   0.0f,  1.0f);

    QMatrix4x4 T5(
            cosf(pt.a5rad()), 0.0f, sinf(pt.a5rad()), 0.0f,
            sinf(pt.a5rad()), 0.0f, -cosf(pt.a5rad()), 0.0f,
            0.0f,  1.0f,  0.0f,  0.0f,
            0.0f,  0.0f,   0.0f,  1.0f);

    QMatrix4x4 T6(
            cosf(pt.a6rad()), -sinf(pt.a6rad()), 0.0f, 0.0f,
            sinf(pt.a6rad()), cosf(pt.a6rad()), 0.0f, 0.0f,
            0.0f,  0.0f,  1.0f,  jt5_len,
            0.0f,  0.0f,   0.0f,  1.0f);

    //переобразование координат из базисиа системы 6го звена в основной осуществляется с помощь. переменожений
    QMatrix4x4 target = T1*T2*T3*T4*T5*T6;
    //поворачиаеам матрицу на 90 градусов вокруг оси Z в соотвестсвие с ск робота
    //target.rotate(static_cast<float>(M_PI/2), QVector3D(0,0,1));
    QMatrix4x4 rt(0.0f, -1.0f, 0.0f, 0.0f,
                  1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f, 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f);
    target = rt * target;
    return target;
}
//------------------------------------------------------------------------------
//вычислеям x,y,z,o,a,t координаты точки
//------------------------------------------------------------------------------
DecartPoint KinTaskSolver::calcDecart(QMatrix4x4 &mat, DecartPoint &curr_xyz)
{
    //DecartPoint curr_xyz(nullptr, DecartPoint::EulerAngles);
    curr_xyz.setX(mat(0,3));
    curr_xyz.setY(mat(1,3));
    curr_xyz.setZ(mat(2,3));
    curr_xyz.setO(atan2(mat(1,2), mat(0,2)) * 180 / M_PI);
    curr_xyz.setA(atan2(pow(1 - pow(mat(2,2), 2), 0.5f), mat(2,2)) * 180 / M_PI);
    curr_xyz.setT((atan2(mat(2,1), mat(2,0)) - M_PI / 2) * 180 / M_PI);
    return curr_xyz;
}
//------------------------------------------------------------------------------
//вспомогательная функция расчета поврота ск
//------------------------------------------------------------------------------
QMatrix4x4 KinTaskSolver::calcR(JTPoint &pt, int pt_amount)
{
    if (pt_amount > 3) return  QMatrix4x4();
    QVector<QMatrix4x4> matrixes;

    QMatrix4x4 R1;
    R1.setToIdentity();
    R1(0,0) = cos(-pt.a1rad()); R1(0,1) = 0; R1(0,2) = sin(-pt.a1rad());
    R1(1,0) = sin(-pt.a1rad()); R1(1,1) = 0; R1(1,2) = -cos(-pt.a1rad());
    R1(2,0) = 0;        R1(2,1) =1;  R1(2,2) = 0;
    matrixes.append(R1);

    //R2
    QMatrix4x4 R2;
    R2.setToIdentity();
    R2(0,0) = cos(M_PI/2 - pt.a2rad()); R2(0,1) = -sin(M_PI/2 -pt.a2rad()); R2(0,2) = 0;
    R2(1,0) = sin(M_PI/2 - pt.a2rad()); R2(1,1) = cos(M_PI/2 -pt.a2rad());  R2(1,2) = 0;
    R2(2,0) = 0;                R2(2,1) =1;                 R2(2,2) = 1;
    matrixes.append(R2);

    //R3
    QMatrix4x4 R3;
    R3.setToIdentity();
    R3(0,0) = cos(M_PI/2 + pt.a3rad()); R3(0,1) = 0; R3(0,2) = sin(M_PI/2 + pt.a3rad());
    R3(1,0) = sin(M_PI/2 + pt.a3rad()); R3(1,1) = 0; R3(1,2) = -cos(M_PI/2 + pt.a3rad());
    R3(2,0) = 0;        R3(2,1) =1;  R3(2,2) = 0;
    matrixes.append(R3);

    QMatrix4x4 res; res.setToIdentity();
    for (int i = 0; i < pt_amount; i++) {
        res *= matrixes[i];
    }
    return res;
}
//------------------------------------------------------------------------------
//решение ОЗК
//------------------------------------------------------------------------------
int KinTaskSolver::solveOZK(DecartPoint &xyz, JTPoint &jpt)
{
//    qDebug() << "x " << xyz.x() << " y " << xyz.y() << " z " << xyz.z() <<  "o " << xyz.o() << " a " << xyz.a() << " t " << xyz.t();
    jt2_len = 355.f;
    jt3_len = 375.f;
    jt5_len = 78.f;

    //матрица вращения инструмента
    QMatrix4x4 R06;
    R06.setToIdentity();
    R06(0,0) = cos(xyz.oRad()) * cos(xyz.aRad()) * cos(xyz.tRad()) - sin(xyz.oRad())*sin(xyz.tRad()); R06(0,1) = -cos(xyz.oRad()) * cos(xyz.aRad()) * sin(xyz.tRad()) - sin(xyz.oRad())*sin(xyz.tRad()); R06(0,2) = cos(xyz.oRad())*sin(xyz.aRad());
    R06(1,0) = sin(xyz.oRad()) * cos(xyz.aRad()) * cos(xyz.tRad()) + cos(xyz.oRad())*sin(xyz.tRad()); R06(1,1) = -sin(xyz.oRad()) * cos(xyz.aRad()) * cos(xyz.tRad()) - cos(xyz.oRad())*sin(xyz.tRad()); R06(1,2) = sin(xyz.oRad())*sin(xyz.aRad());
    R06(2,0) = -sin(xyz.aRad()) * cos(xyz.tRad()); R06(2,1) = sin(xyz.aRad()) * cos(xyz.tRad()); R06(2,2) = cos(xyz.aRad());
//    for (int r = 0; r < 3; r++) {
//        for (int c = 0; c < 3; c++) {
//            qDebug() << "r " << r << " c " << c << " " << R06(r,c);
//        }
//    }
    //вектор положения инструмена
    QVector3D Pt(xyz.x(), xyz.y(), xyz.z());
    //рассчитаем коордианты сочленения Pt4 в базоваой СК
    QVector3D R6vec=  R06.mapVector(QVector3D(0,0,1)) * jt5_len;
    QVector3D P4 = Pt - R6vec;
//    qDebug() << "P4 x" <<  P4.x() << " P4y " << P4.y() << " P4z " << P4.z();
//    qDebug() << "R6 x" <<  R6vec.x() << " R6y " << R6vec.y() << " R6z " << R6vec.z();

    //рассчитаем угол jt1 для положитльеной полуплосоксти (игнорируя угол atan(P4y,P4x) - pi)
    QVector3D P1(offset_x, offset_y, offset_z);
    float a1 = fabs(P4.x()) > 0.01f ?  atan2(P4.y() - P1.y(), P4.z() - P1.z()) : 0;
    //qDebug() << "a1 " << a1 * 180 / M_PI;
    jpt.setA1Rad(a1);

    //расчет  вспомогательных линий
    float la = powf(powf(P4.x(), 2) + powf(P4.y(), 2) + powf(P4.z(), 2), 0.5);
    float lb = P4.z() - P1.z();
    float lc = powf(powf(P4.x(), 2) + powf(P4.y(), 2), 0.5);
    //проверка гометии достидимотси точки P4
    if ((la > jt3_len + jt2_len) || (la < fabs(jt2_len - jt3_len))) {
       // qDebug() << "la " << la;
        return ReachError;
    }
    //расчет theta3
    float cos3 = (powf(lb,2) +powf(lc,2) - powf(jt2_len,2) - powf(jt3_len, 2)) / (2 *jt2_len * jt3_len);
    //qDebug() << "c3 " << cos3;

    //расчет theta2 для каждого из theta3
    if (lc > 0.01)
    {
        //раскрываем аркосинус с минусом и с плюсом
        float a3p = acos(cos3);
        float a3n = -acos(cos3);

        float appha = lc > 0.01 ?  atan2(lb,lc) : 0;
        float beta_p = atan2(jt3_len * sin(a3p), jt2_len + jt3_len * cos3);
        float a2p = M_PI / 2 - (appha - beta_p);
        float beta_n = atan2(jt3_len * sin(a3n), jt2_len + jt3_len * cos3);
        float a2n = M_PI / 2 - (appha - beta_n);

        QMatrix4x4 R2p;
        R2p.setToIdentity();
        R2p(0,0) = cos(M_PI/2 - a2p); R2p(0,1) = -sin(M_PI/2 -a2p); R2p(0,2) = 0;
        R2p(1,0) = sin(M_PI/2 - a2p); R2p(1,1) = cos(M_PI/2 -a2p);  R2p(1,2) = 0;
        R2p(2,0) = 0;                 R2p(2,1) =1;                  R2p(2,2) = 1;

        QMatrix4x4 R2n;
        R2n.setToIdentity();
        R2n(0,0) = cos(M_PI/2 - a2n); R2n(0,1) = -sin(M_PI/2 -a2n); R2n(0,2) = 0;
        R2n(1,0) = sin(M_PI/2 - a2n); R2n(1,1) = cos(M_PI/2 -a2n);  R2n(1,2) = 0;
        R2n(2,0) = 0;                 R2n(2,1) =1;                  R2n(2,2) = 1;

        QMatrix4x4 R02p = calcR(jpt,1) * R2p;
        QMatrix4x4 R02n = calcR(jpt,1) * R2n;

        //расчет точек P3
        QVector3D P3p(R2p(0,0),R2p(1,0), R2p(2,0));
        P3p *= jt2_len;

        QVector3D P3n(R2n(0,0),R2n(1,0), R2n(2,0));
        P3n *= jt2_len;

        //выбираем знак по значению координаты z векторов P3p P3n
        float a3 = P3p.z() > P3n.z() ? a3p : a3n;
       // qDebug() << "a3 " << a3 * 180 / M_PI;
        jpt.setA3Rad(a3);

        //перерасчет theta2
        float beta = atan2(jt3_len * sin(a3), jt2_len + jt3_len * cos3);
        float a2 = M_PI / 2 - (appha - beta);
       // qDebug() << "a2 " << a2 * 180 / M_PI;
        jpt.setA2Rad(a2);
    }
    else {
        //если С==0 - устивавлваем оси jt2 jt3 в ноль
        jpt.setA2Rad(0);
        jpt.setA3Rad(0);
        qDebug() << "zerr";
    }

    //Расчет матрицы поворота системы координат третьей точки относительно базовой ситемы координат
    QMatrix4x4 rt;
    rt.setToIdentity();
    rt(0,0) = 0.0f; rt(0,1) = -1.0f; rt(0,2) = 0.0f;
    rt(1,0) = 1.0f; rt(1,1) = 0.0f;  rt(1,2) = 0.0f;
    rt(2,0) = 0.0f; rt(2,1) = 0.0f;  rt(2,2) = 1.0f;
    QMatrix4x4 R30 = rt * calcR(jpt, 3);
    //расчет смщениея системы коодринат шестой точки относительно системы коордиант третьей
    QMatrix4x4 R36 = R30.transposed() * R06;
    //расчте угла jt5
    float a5 = atan2(R36(0,2),R36(2,2));
    //qDebug() << "a5 " << a5 * 180 / M_PI;
    jpt.setA5Rad(a5);

    //пока устанваливаем как нули
    jpt.setA4(0);
    jpt.setA6(0);
    return  checkPointRange(jpt);
}
//------------------------------------------------------------------------------
//проекрка угловых координат
//------------------------------------------------------------------------------
int KinTaskSolver::checkPointRange(JTPoint &pt)
{
//    //прверка диапазлна jt1
//    if ((pt.a1() < j1_min) || (pt.a1() > j1_max)) {
//        return JT1_Error;
//    }
//    //прверка диапазлна jt2
//    else if ((pt.a2() < j2_min ) || (pt.a2() > j2_max)) {
//        return JT2_Error;
//    }
//    //прверка диапазлна jt3
//    else if ((pt.a3() < j3_min ) || (pt.a3() > j3_max)) {
//        return JT3_Error;
//    }
//    //прверка диапазлна jt3
//    else if ((pt.a4() < j4_min ) || (pt.a4() > j4_max)) {
//        return JT4_Error;
//    }
    //прверка диапазлна jt5
    if ((pt.a5() < j5_min ) || (pt.a5() > j5_max)) {
        qDebug() << " a5 " << pt.a5() << " min " << j5_min << " max " << j5_max;
        return JT5_Error;
    }
    return 1;
}
