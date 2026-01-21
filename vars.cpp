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
    jt2_len = 355;
    jt3_len = 375;
    jt5_len = 78;

    offset_x = 0;
    offset_y = 0;
    offset_z = 0;
}
//------------------------------------------------------------------------------
KinTaskSolver::KinTaskSolver(float jt2, float jt3, float jt5)
{
    jt2_len = jt2;
    jt3_len = jt3;
    jt5_len = jt5;

    offset_x = 0;
    offset_y = 0;
    offset_z = 0;
}
//------------------------------------------------------------------------------
void KinTaskSolver::loadGeometry()
{
    jt3_len = 375.0f;
    jt2_len = 355.0f;
    jt5_len = 78.0f;
}
//------------------------------------------------------------------------------
JTPoint KinTaskSolver::calcJT_Hor(QVector3D &xyz, float angle)
{
    JTPoint jpt;

    //считаем координтаы инструмента на плоскости
    double localX = sqrt(pow((offset_x - xyz.x()), 2) + pow((offset_y - xyz.y()), 2));
    double localY = xyz.z() - offset_z;

    jpt.setA1(atan2(xyz.y() - offset_y, xyz.x() - offset_x));
    //расчет p4
    double yP4 = sin(angle) * jt5_len + localY;
    double xP4 = localX - std::cos(angle) * jt5_len;
    //дистания p4-p2
    double distanceSmall = sqrt(pow((xP4), 2) + pow((yP4), 2));
    //счтиаем углы
    if (distanceSmall < jt2_len + jt3_len)
    {
        float y3 = acos((pow(distanceSmall, 2) + pow(jt2_len, 2) - pow(jt3_len, 2))
                  / (2 * distanceSmall * jt2_len));
        //расчет JT2
        jpt.setA2(M_PI_2 - y3 -  asin(yP4 / distanceSmall));
        //расчет JT3
//        jointGroupPositions[ikParams.joints[2]] = M_PI
//            - std::acos((pow(ikParams.d1, 2) + pow(ikParams.d2, 2) - pow(distanceSmall, 2))
//                        / (2 * ikParams.d1 * ikParams.d2));
        //JT 4 всегда 0
        jpt.setA4(0);
        //расчет JT5
//        jointGroupPositions[ikParams.joints[5]] = ikParams.angleThreeDirection
//            * (M_PI - (M_PI_2 - angle)
//               - (jointGroupPositions[ikParams.joints[1]]
//                  + jointGroupPositions[ikParams.joints[2]]));
        //JT6 всегда ноль (для текущих инструментов)
        jpt.setA6(0);
    }
    return  jpt;
}
//------------------------------------------------------------------------------
//Решегие ПЗК
//------------------------------------------------------------------------------
QMatrix4x4 KinTaskSolver::solvePZK(JTPoint &pt)
{
    jt2_len = 355;
    jt3_len = 375;
    jt5_len = 78;

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
QVector3D KinTaskSolver::calcXyz(QMatrix4x4 &mat)
{
    QVector3D curr_xyz;
    curr_xyz.setX(mat(0,3));
    curr_xyz.setY(mat(1,3));
    curr_xyz.setZ(mat(2,3));
    return curr_xyz;
}
//------------------------------------------------------------------------------
EulerAngles KinTaskSolver::calcOat(QMatrix4x4 &mat)
{
    EulerAngles target_oat;
    target_oat[1] = atan2(pow(1 - pow(mat(2,2), 2), 0.5f), mat(2,2)) * 180 / M_PI;
    target_oat[0] = atan2(mat(1,2), mat(0,2)) * 180 / M_PI;
    target_oat[2] = (atan2(mat(2,1), mat(2,0)) - M_PI / 2) * 180 / M_PI;
    return  target_oat;
}
//------------------------------------------------------------------------------


