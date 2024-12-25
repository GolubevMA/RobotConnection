#ifndef TROBOTMODEL_H
#define TROBOTMODEL_H

#include <QVector3D>
#include <QVector2D>
#include "GL/gl.h"
#include <qgl.h>

//------------------------------------------------------------------------------s
//класс инкапсулиюущий
//геометрию двжижущейся части (детали) робота
//------------------------------------------------------------------------------
class RbotPart
{
public:
    //стурктруа инкапсулирующая точку
    // в вершинном буффере OPENGL
    struct VertexData
    {
        QVector3D position;
        QVector2D texCoord;
    };
    static const int MaxPtCount = 100;

    //чилос точкек
    int PointCount = 0;
    //число индексов
    int IndexCount = 0;
    //массив вершин
    VertexData *vertices;
    //массив индексов
    GLuint *indexes;

    RbotPart();
    RbotPart(int pt_count, int ind_ocunt, VertexData *vert, GLuint *ind);
    ~RbotPart();

};

//------------------------------------------------------------------------------
//класс инкапсулирющий модель робота (список деталей и описание их расположения)
//------------------------------------------------------------------------------
class TRobotModel
{
public:

    //число деталей робота
    int DetalCount;
    //сипскок деталей робота
    QList<RbotPart> DetalList;
    //список тоек распложения детлей в прострнтсве относительно
    // центра предыдущей детали
    QList<QVector3D> ConnectionPoints;
    //оси относительно которых вращамем детали робота
    // (в opengl оси Z и Y меняются местами)
    QList<QVector3D> RotationAxis;

    TRobotModel();
    ~TRobotModel();

    void loadModel();
};
//-----------------------------------------------------------------------------

#endif // TROBOTMODEL_H
