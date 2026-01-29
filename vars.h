#ifndef VARS_H
#define VARS_H

/*
    Программа RobotMotion реализует програмированиия движения робота - сканирующего образец контроля на основе загрженной модели

    Программа реализовывает нестколко сценариев сканирвоания в зависимости от выбранного датчика
        - обход выделенной пользователем поверхности step модели с удрежанием датчика перпендиклурно сакнирумеой поверхности
        - скан отверстий внутритурным датчиаком

    Робот управляет доплнитедлбной осью, кторая вращает стенд с деталью

    Смена датичка осуществляется поутем перменещния рбота к нужному дачтику на стенде

    Необходимо  осуществлять проверку фактического погложения модели на стедне номимльному
    Проверку делать либо камерой либо датичком нажатия

    Обшение с роботом происхдит по протокулу TCP-IP с помощью команд в форматет string

*/
//------------------------------------------------------------------------------
#include <Qt>
#include <QObject>
#include <QList>
#include "STEPControl_Reader.hxx"
#include "STEPCAFControl_Reader.hxx"
#include "STEPControl_Controller.hxx"
#include  "BRepBuilderAPI_Transform.hxx"
#include <gp_Ax1.hxx>
#include <AIS_Shape.hxx>
#include <AIS_Point.hxx>
#include <Geom_Point.hxx>
#include "StepData_StepModel.hxx"
#include  "Standard_Transient.hxx"
#include  "Interface_EntityIterator.hxx"
#include  "XSControl_TransferReader.hxx"
#include  "XSControl_WorkSession.hxx"
#include  "StepRepr_NextAssemblyUsageOccurrence.hxx"
#include  "Transfer_Binder.hxx"
#include  "TransferBRep.hxx"
#include  "Transfer_TransientProcess.hxx"
#include  "StepBasic_ProductDefinition.hxx"
#include  "StepBasic_Product.hxx"
#include  "XSControl_WorkSession.hxx"
#include  "StepRepr_RepresentationItem.hxx"
#include  "StepBasic_PlaneAngleUnit.hxx"
#include  "gp_Quaternion.hxx"
#include  "Graphic3d_TransformPers.hxx"
#include  "Geom2d_Circle.hxx"
#include  "gp_Circ2d.hxx"
#include  "BRepBuilderAPI_MakeVertex.hxx"
#include  "TopOpeBRep_ShapeIntersector.hxx"
#include  "TopoDS.hxx"
#include <V3d_View.hxx>
#include "jtpoint.h"
#include "decartpoint.h"
#include "math.h"
//------------------------------------------------------------------------------
// Параметры взуалиции устанвки контроля
//------------------------------------------------------------------------------
struct ControlSystemModel
{
    int RobotsAmount;       //число роботв (от 1 до 2х)

    QList<gp_Ax1> rotateDirections;         //список  векторв, относитедльно которых вращаются подвижные детали системы
                                            // (детали робота)

    QList<Handle(AIS_Shape)>  robotShape;   //списко shape ов подвижых деталей  модели (осей робота)
    QList<Handle(AIS_Shape)>  staticShape;  //неподыижные детали  обьдиням в один shape

    bool Created;

    ControlSystemModel();

    //процедруа загрузки чсистемф из step файла
    void LoadSystemModel(QString filename);

};
//------------------------------------------------------------------------------
//class EulerAngles
//{
//    static const int PointCount = 3;

//    EulerAngles() {
//        memset(mPoints, 0, sizeof(PointCount));
//    }

//    //устновка углов суставов
//    void setO(float a) {mPoints[0] = a;}
//    void setA(float a) {mPoints[1] = a;}
//    void setT(float a) {mPoints[2] = a;}

//    //получение углов суставово
//    float o() {return  mPoints[0];}
//    float a() {return  mPoints[1];}
//    float t() {return  mPoints[2];}

//    //получение i-й точки сипска
//    float& operator[](int index) {
//        return mPoints[index];
//    }

//    float operator[](int i) const {
//        return mPoints[i];
//    }

//    int size() {
//        //return mPoints.size();
//        return  PointCount;
//    }

//    //список точек
//    float mPoints[PointCount];
//};
typedef  QVector3D EulerAngles;
//------------------------------------------------------------------------------
//класс инкапуслирубщий решение задачи прямого / обратного позицицонирования
// для робота с заднными харакетристиками
//------------------------------------------------------------------------------
class KinTaskSolver
{
public :

    enum OZK_Errors {JT5_Error=-5,JT4_Error,JT3_Error,JT2_Error,JT1_Error,ReachError, NoError};

    KinTaskSolver();
    //KinTaskSolver(float jt2, float jt3, float jt5);

    //прямое позиционирование
    QMatrix4x4 solvePZK(JTPoint &pt);
    static DecartPoint calcDecart(QMatrix4x4 &mat, DecartPoint &curr_xyz);
    //обратное позиционироване
    //JTPoint calcJT_Vert(QVector3D &xyz, float amgle);
    int solveOZK(DecartPoint &xyz, JTPoint &jpt);

    void loadGeometry();

private:
    float jt2_len;
    float jt3_len;
    float jt5_len;

    //смщения точки P2 ()
    float offset_x;
    float offset_y;
    float offset_z;

    //диапазоны углов
    float j1_min, j1_max;
    float j2_min, j2_max;
    float j3_min, j3_max;
    float j4_min, j4_max;
    float j5_min, j5_max;
    float j6_min, j6_max;

    QMatrix4x4 calcR(JTPoint &pt, int pt_amount);
    int checkPointRange(JTPoint &pt);

};
//------------------------------------------------------------------------------
//класс инкапсулирующаий модель сканирования
//------------------------------------------------------------------------------
class ScanModel
{
public :
    int modelType;

};

//------------------------------------------------------------------------------
#endif // VARS_H
