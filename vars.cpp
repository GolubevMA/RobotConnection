#include "vars.h"
#include "qdebug.h"
//------------------------------------------------------------------------------
ControlSystemModel::ControlSystemModel()
{
//    rotateDirections << gp_Ax1(gp_Pnt(0,0,0), gp_Dir(0,0,1)) << gp_Ax1(gp_Pnt(100,0,360),gp_Dir(1,0,0)) << gp_Ax1(gp_Pnt(0,0,720),gp_Dir(1,0,0))
//                << gp_Ax1(gp_Pnt(0,0,720),gp_Dir(0,0,1)) <<gp_Ax1(gp_Pnt(100,0,1086),gp_Dir(1,0,0)) <<gp_Ax1(gp_Pnt(0,0,0),gp_Dir(0,0,1));
    robotShape.clear();
}
//------------------------------------------------------------------------------
// модель сисьтемы контроля разделятся на подвижные детали (оси робота ) и непожвижные
//-----------------------------------------------------------------------------
void ControlSystemModel::LoadSystemModel(QString filename)
{
    //парсин STEP
    //Standard_CString fname = filename.toLocal8Bit().data();
    Standard_CString fname = "J:\\test\\occt-samples-qopenglwidget-master\\occt-qopenglwidget\\RS007N-BC01.stp";

    STEPControl_Reader step_reader;
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

    //фигруы подвижных осей робота
    QList<TopoDS_Shape> jt_solids;
    //остальбные фигуры модели
    QList<TopoDS_Shape> othetr_solids;

    //проходимся по всем фигурам в данном наборе
    for(TopoDS_Iterator anIt(aShape); anIt.More(); anIt.Next())
    {
        const TopoDS_Shape &curShape = anIt.Value();
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
                        jt_solids << curShape;
                        qDebug() << "axis " << derailName;
                    }
                    else {
                        //добавляе в список остальных деталей
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
                const TopoDS_Shape &curShape1 = anExp.Value();
                TopAbs_ShapeEnum type1 = curShape1.ShapeType();

                //здесть можно тоже проыерять, если явлеятся частью робота
                if (type1 == TopAbs_SOLID)
                {
                    //добавляе в список остальных деталей
                    othetr_solids << curShape;
                }
            }
        }
    }


    //фомриурем набор нормалей к плоскостям
    //отнсительно которых вращаются оси робота

    rotateDirections.clear();
    rotateDirections.append(gp_Ax1(gp_Pnt(0,0,0), gp_Dir(0,0,1)));

    for (int i = 1; i < jt_solids.length(); i++)
    {
        //пересечения текущей  детали  с предыдущей
        TopOpeBRep_ShapeIntersector inspect;
        inspect.InitIntersection(jt_solids.at(i-1), jt_solids.at(i));

        //поверхность  пересчения набо выбрасть меньшую по площаи
        TopoDS_Shape s1 = inspect.CurrentGeomShape(i == 4 ? 1 : 2);
        if( s1.ShapeType() == TopAbs_FACE)
        {
            TopoDS_Face face = TopoDS::Face(s1);
            //елси повернсть является послоктью
            BRepAdaptor_Surface surface = BRepAdaptor_Surface(face);
            if (surface.GetType() == GeomAbs_Plane) {
                qDebug() << "is plnae " << i;
                //получаем нормаль к полсокости в точкре крепления
                rotateDirections.append(surface.Plane().Axis());
            }
        }
    }



    //здесь все детали стачиные shapes надо обьединиьт  в  один
    staticShape = new AIS_Shape(othetr_solids.at(0));
    //    //отриосваем сосотваные детали
    //    for(int i=0; i< othetr_solids.length(); i++)
    //    {
    //        //myContext->Display(anAIS_Shape,AIS_Shaded, 0 ,false);

    //    }

    //формируем список осей
    robotShape.clear();
    for(int i=0; i< jt_solids.length(); i++)
    {
        jt_solids[i].Orientation(TopAbs_Orientation::TopAbs_FORWARD);
        Handle(AIS_Shape) anAIS_Shape = new AIS_Shape(jt_solids[i]);
        robotShape.append(anAIS_Shape);
    }
}


