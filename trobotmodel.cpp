#include "trobotmodel.h"
#include "qdebug.h"
//------------------------------------------------------------------------------
RbotPart::RbotPart()
{
    PointCount = 0;
    IndexCount = 0;
    vertices = NULL;
    indexes = NULL;
}
//------------------------------------------------------------------------------
RbotPart::RbotPart(int pt_count, int ind_ocunt, VertexData *vert, GLuint *ind)
{
    PointCount = pt_count;
    IndexCount = ind_ocunt;
    vertices = vert;
    indexes = ind;
}
//------------------------------------------------------------------------------
//удаелям выделнную под массивы память
//------------------------------------------------------------------------------
RbotPart::~RbotPart()
{
//    if (vertices != NULL)
//    {
//        delete vertices;
//        vertices = NULL;
//    }
//    if (indexes != NULL)
//    {
//        delete indexes;
//        indexes = NULL;
//    }
}
//------------------------------------------------------------------------------
TRobotModel::TRobotModel()
{
    DetalCount = 0;
    DetalList.clear();
    ConnectionPoints.clear();
}
//------------------------------------------------------------------------------
TRobotModel::~TRobotModel()
{
    DetalList.clear();
    ConnectionPoints.clear();
    DetalCount = 0;
}
//------------------------------------------------------------------------------
void TRobotModel::loadModel()
{
    DetalList.clear();
    DetalCount = 0;
    ConnectionPoints.clear();

    QVector3D v1,v2,v3;
    int vert_count;
    int ind_count;

    //ось 1
    vert_count = 24;
    ind_count = 36;
    RbotPart RobotAxis1 =  RbotPart(
        vert_count,
        ind_count,
        new RbotPart::VertexData[vert_count]
        {
            //передняя грань
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(2.0/4.0, 1.0/3.0)},  // v0
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(1.0/4.0, 1.0/3.0)}, // v1
            {QVector3D(-1.0f,  0.7f,  0.8f), QVector2D(2.0/4.0, 2.0/3.0)},  // v2
            {QVector3D( 1.0f,  0.7f,  0.8f), QVector2D(1.0/4.0, 2.0/3.0)}, // v3

            //левая грань
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(1.0/4.0, 1.0/3.0)}, // v4
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.0f, 1.0/3.0)}, // v5
            {QVector3D( 1.0f,  0.7f,  0.8f), QVector2D(1.0/4.0, 2.0/3.0)},  // v6
            {QVector3D( 1.0f,  0.7f, -0.8f), QVector2D(0.0f, 2.0/3.0)}, // v7

            //задняя грань
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0f, 1.0/3.0)}, // v8
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(3.0/4.0, 1.0/3.0)},  // v9
            {QVector3D( 1.0f,  0.7f, -0.8f), QVector2D(1.0f, 2.0/3.0)}, // v10
            {QVector3D(-1.0f,  0.7f, -0.8f), QVector2D(3.0/4.0, 2.0/3.0)},  // v11

            //правая грань
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(3.0/4.0, 1.0/3.0)}, // v12
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(2.0/4.0, 1.0/3.0)},  // v13
            {QVector3D(-1.0f,  0.7f, -0.8f), QVector2D(3.0/4.0, 2.0/3.0)}, // v14
            {QVector3D(-1.0f,  0.7f,  0.8f), QVector2D(2.0/4.0, 2.0/3.0)},  // v15

            //нижняя грань
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(2.0/4.0, 1.0f)}, // v16
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0/4.0, 1.0f)}, // v17
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(1.0/4.0, 2.0/3.0)}, // v19
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(2.0/4.0, 2.0/3.0)}, // v18

            //верзняя грань
            {QVector3D(-1.0f,  0.7f,  0.8f), QVector2D(1.0/4.0, 1.0/3.0)}, // v20
            {QVector3D( 1.0f,  0.7f,  0.8f), QVector2D(2.0/4.0, 1.0/3.0)}, // v21
            {QVector3D( 1.0f,  0.7f, -0.8f), QVector2D(2.0/4.0, 0)},  // v23
            {QVector3D(-1.0f,  0.7f, -0.8f), QVector2D(1.0/4.0, 0)} // v22
        },

        new GLuint[ind_count] {
            0,  1,  2,  2,  1, 3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  5,  6,  6,  5, 7,      // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  9, 10, 10, 9, 11,      // Face 2 - triangle strip ( v8,  v9, v10, v11)
           12, 13, 14, 14, 13, 15,     // Face 3 - triangle strip (v12, v13, v14, v15)
           16, 17, 18, 18, 19, 16,     // Face 4 - triangle strip (v16, v17, v18, v19)
           20, 21, 22, 22, 23, 20      // Face 5 - triangle strip (v20, v21, v22, v23)
        }
    );


    DetalList.append(RobotAxis1);
    ConnectionPoints.append(QVector3D(0,0,0));
    //деталь вращается отностительно оси Y
    RotationAxis.append(QVector3D(0,1,0));
    DetalCount++;

    qDebug() << "iiii " << DetalList[0].IndexCount;

    //ось 2
    vert_count = 24;
    ind_count = 36;
    RbotPart RobotAxis2 =  RbotPart(
        vert_count,
        ind_count,
        new RbotPart::VertexData[vert_count]
        {
            //передняя грань
            {QVector3D(-1.5f, -1.4f,  0.7f), QVector2D(2.0/4.0, 1.0/3.0)},  // v0
            {QVector3D( -1.0f, -1.4f,  0.7f), QVector2D(1.0/4.0, 1.0/3.0)}, // v1
            {QVector3D(-1.5f,  2.0f,  0.7f), QVector2D(2.0/4.0, 2.0/3.0)},  // v2
            {QVector3D( -1.0f,  2.0f,  0.7f), QVector2D(1.0/4.0, 2.0/3.0)}, // v3

            //левая грань
            {QVector3D( -1.0f, -1.4f,  0.7f), QVector2D(1.0/4.0, 1.0/3.0)}, // v4
            {QVector3D( -1.0f, -1.4f, -0.7f), QVector2D(0.0f, 1.0/3.0)}, // v5
            {QVector3D( -1.0f,  2.0f,  0.7f), QVector2D(1.0/4.0, 2.0/3.0)},  // v6
            {QVector3D( -1.0f,  2.0f, -0.7f), QVector2D(0.0f, 2.0/3.0)}, // v7

            //задняя грань
            {QVector3D( -1.0f, -1.4f, -0.7f), QVector2D(1.0f, 1.0/3.0)}, // v8
            {QVector3D(-1.5f, -1.4f, -0.7f), QVector2D(3.0/4.0, 1.0/3.0)},  // v9
            {QVector3D(-1.0f,  2.0f, -0.7f), QVector2D(1.0f, 2.0/3.0)}, // v10
            {QVector3D(-1.5f,  2.0f, -0.7f), QVector2D(3.0/4.0, 2.0/3.0)},  // v11

            //правая грань
            {QVector3D(-1.5f, -1.4f, -0.7f), QVector2D(3.0/4.0, 1.0/3.0)}, // v12
            {QVector3D(-1.5f, -1.4f,  0.7f), QVector2D(2.0/4.0, 1.0/3.0)},  // v13
            {QVector3D(-1.5f,  2.0f, -0.7f), QVector2D(3.0/4.0, 2.0/3.0)}, // v14
            {QVector3D(-1.5f,  2.0f,  0.7f), QVector2D(2.0/4.0, 2.0/3.0)},  // v15

            //нижняя грань
            {QVector3D(-1.5f, -1.4f, -0.7f), QVector2D(2.0/4.0, 1.0f)}, // v16
            {QVector3D( -1.0f, -1.4f, -0.7f), QVector2D(1.0/4.0, 1.0f)}, // v17
            {QVector3D( -1.0f, -1.4f,  0.7f), QVector2D(1.0/4.0, 2.0/3.0)}, // v19
            {QVector3D(-1.5f, -1.4f,  0.7f), QVector2D(2.0/4.0, 2.0/3.0)}, // v18

            //верзняя грань
            {QVector3D(-1.5f,  2.0f,  0.7f), QVector2D(1.0/4.0, 1.0/3.0)}, // v20
            {QVector3D( -1.0f,  2.0f,  0.7f), QVector2D(2.0/4.0, 1.0/3.0)}, // v21
            {QVector3D( -1.0f,  2.0f, -0.7f), QVector2D(2.0/4.0, 0)},  // v23
            {QVector3D(-1.5f,  2.0f, -0.7f), QVector2D(1.0/4.0, 0)} // v22
        },

        new GLuint[ind_count] {
            0,  1,  2,  2,  1, 3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  5,  6,  6,  5, 7,      // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  9, 10, 10, 9, 11,      // Face 2 - triangle strip ( v8,  v9, v10, v11)
           12, 13, 14, 14, 13, 15,     // Face 3 - triangle strip (v12, v13, v14, v15)
           16, 17, 18, 18, 19, 16,     // Face 4 - triangle strip (v16, v17, v18, v19)
           20, 21, 22, 22, 23, 20      // Face 5 - triangle strip (v20, v21, v22, v23)
        }
    );

    DetalList.append(RobotAxis2);
    ConnectionPoints.append(QVector3D(0,2,0));
    //вращаем отностиедбно вектора
    //перпедникулярного левой грании перовй детали
    v1 = QVector3D( -1.0f,  2.0f,  0);
    v2 = QVector3D( -1.0f, -1.4f, -0.7f);
    v3= QVector3D( -1.0f, -1.4f,  0);
    RotationAxis.append(QVector3D::normal(v1,v2,v3));
    DetalCount++;



    //ось 3
    vert_count = 24;
    ind_count = 36;
    RbotPart RobotAxis3 =  RbotPart(
        vert_count,
        ind_count,
        new RbotPart::VertexData[vert_count]
        {
            //передняя грань
            {QVector3D(-0.8f, -0.8f,  1.0f), QVector2D(2.0/4.0, 1.0/3.0)},  // v0
            {QVector3D( 0.8f, -0.8f,  1.0f), QVector2D(1.0/4.0, 1.0/3.0)}, // v1
            {QVector3D(-0.8f,  0.8f,  1.0f), QVector2D(2.0/4.0, 2.0/3.0)},  // v2
            {QVector3D( 0.8f,  0.8f,  1.0f), QVector2D(1.0/4.0, 2.0/3.0)}, // v3

            //левая грань
            {QVector3D( 0.8f, -0.8f,  1.0f), QVector2D(1.0/4.0, 1.0/3.0)}, // v4
            {QVector3D( 0.8f, -0.8f, -1.0f), QVector2D(0.0f, 1.0/3.0)}, // v5
            {QVector3D( 0.8f,  0.8f,  1.0f), QVector2D(1.0/4.0, 2.0/3.0)},  // v6
            {QVector3D( 0.8f,  0.8f, -1.0f), QVector2D(0.0f, 2.0/3.0)}, // v7

            //задняя грань
            {QVector3D( 0.8f, -0.8f, -1.0f), QVector2D(1.0f, 1.0/3.0)}, // v8
            {QVector3D(-0.8f, -0.8f, -1.0f), QVector2D(3.0/4.0, 1.0/3.0)},  // v9
            {QVector3D( 0.8f,  0.8f, -1.0f), QVector2D(1.0f, 2.0/3.0)}, // v10
            {QVector3D(-0.8f,  0.8f, -1.0f), QVector2D(3.0/4.0, 2.0/3.0)},  // v11

            //правая грань
            {QVector3D(-0.8f, -0.8f, -1.0f), QVector2D(3.0/4.0, 1.0/3.0)}, // v12
            {QVector3D(-0.8f, -0.8f,  1.0f), QVector2D(2.0/4.0, 1.0/3.0)},  // v13
            {QVector3D(-0.8f,  0.8f, -1.0f), QVector2D(3.0/4.0, 2.0/3.0)}, // v14
            {QVector3D(-0.8f,  0.8f,  1.0f), QVector2D(2.0/4.0, 2.0/3.0)},  // v15

            //нижняя грань
            {QVector3D(-0.8f, -0.8f, -1.0f), QVector2D(2.0/4.0, 1.0f)}, // v16
            {QVector3D( 0.8f, -0.8f, -1.0f), QVector2D(1.0/4.0, 1.0f)}, // v17
            {QVector3D( 0.8f, -0.8f,  1.0f), QVector2D(1.0/4.0, 2.0/3.0)}, // v19
            {QVector3D(-0.8f, -0.8f,  1.0f), QVector2D(2.0/4.0, 2.0/3.0)}, // v18

            //верзняя грань
            {QVector3D(-0.8f,  0.8f,  1.0f), QVector2D(1.0/4.0, 1.0/3.0)}, // v20
            {QVector3D  ( 0.8f,  0.8f,  1.0f), QVector2D(2.0/4.0, 1.0/3.0)}, // v21
            {QVector3D( 0.8f,  0.8f, -1.0f), QVector2D(2.0/4.0, 0)},  // v23
            {QVector3D(-0.8f,  0.8f, -1.0f), QVector2D(1.0/4.0, 0)} // v22
        },

        new GLuint[ind_count] {
            0,  1,  2,  2,  1, 3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  5,  6,  6,  5, 7,      // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  9, 10, 10, 9, 11,      // Face 2 - triangle strip ( v8,  v9, v10, v11)
           12, 13, 14, 14, 13, 15,     // Face 3 - triangle strip (v12, v13, v14, v15)
           16, 17, 18, 18, 19, 16,     // Face 4 - triangle strip (v16, v17, v18, v19)
           20, 21, 22, 22, 23, 20      // Face 5 - triangle strip (v20, v21, v22, v23)
        }
    );

    DetalList.append(RobotAxis3);
    ConnectionPoints.append(QVector3D(-0.2,2,0));
    //вращаем относительно вектора
    //перпедникулярного правой грани второй детали
    v1 = RobotAxis2.vertices[14].position; //v14
    v2 = RobotAxis2.vertices[13].position; //v13
    v3= RobotAxis2.vertices[12].position; //v12
    RotationAxis.append(QVector3D::normal(v1,v2,v3));
    DetalCount++;

    //ось 4
    vert_count = 24;
    ind_count = 36;
    RbotPart RobotAxis4 =  RbotPart(
        vert_count,
        ind_count,
        new RbotPart::VertexData[vert_count]
        {
            //передняя грань
            {QVector3D(-0.5f, -0.5f,  1.5f), QVector2D(2.0/4.0, 1.0/3.0)},  // v0
            {QVector3D( 0.5f, -0.5f,  1.5f), QVector2D(1.0/4.0, 1.0/3.0)}, // v1
            {QVector3D(-0.5f,  0.5f,  1.5f), QVector2D(2.0/4.0, 2.0/3.0)},  // v2
            {QVector3D( 0.5f,  0.5f,  1.5f), QVector2D(1.0/4.0, 2.0/3.0)}, // v3

            //левая грань
            {QVector3D( 0.5f, -0.5f,  1.5f), QVector2D(1.0/4.0, 1.0/3.0)}, // v4
            {QVector3D( 0.5f, -0.5f, -1.0f), QVector2D(0.0f, 1.0/3.0)}, // v5
            {QVector3D( 0.5f,  0.5f,  1.5f), QVector2D(1.0/4.0, 2.0/3.0)},  // v6
            {QVector3D( 0.5f,  0.5f, -1.0f), QVector2D(0.0f, 2.0/3.0)}, // v7

            //задняя грань
            {QVector3D( 0.5f, -0.5f, -1.0f), QVector2D(1.0f, 1.0/3.0)}, // v8
            {QVector3D(-0.5f, -0.5f, -1.0f), QVector2D(3.0/4.0, 1.0/3.0)},  // v9
            {QVector3D( 0.5f,  0.5f, -1.0f), QVector2D(1.0f, 2.0/3.0)}, // v10
            {QVector3D(-0.5f,  0.5f, -1.0f), QVector2D(3.0/4.0, 2.0/3.0)},  // v11

            //правая грань
            {QVector3D(-0.5f, -0.5f, -1.0f), QVector2D(3.0/4.0, 1.0/3.0)}, // v12
            {QVector3D(-0.5f, -0.5f,  1.5f), QVector2D(2.0/4.0, 1.0/3.0)},  // v13
            {QVector3D(-0.5f,  0.5f, -1.0f), QVector2D(3.0/4.0, 2.0/3.0)}, // v14
            {QVector3D(-0.5f,  0.5f,  1.5f), QVector2D(2.0/4.0, 2.0/3.0)},  // v15

            //нижняя грань
            {QVector3D(-0.5f, -0.5f, -1.0f), QVector2D(2.0/4.0, 1.0f)}, // v16
            {QVector3D( 0.5f, -0.5f, -1.0f), QVector2D(1.0/4.0, 1.0f)}, // v17
            {QVector3D( 0.5f, -0.5f,  1.5f), QVector2D(1.0/4.0, 2.0/3.0)}, // v19
            {QVector3D(-0.5f, -0.5f,  1.5f), QVector2D(2.0/4.0, 2.0/3.0)}, // v18

            //верзняя грань
            {QVector3D(-0.5f,  0.5f,  1.5f), QVector2D(1.0/4.0, 1.0/3.0)}, // v20
            {QVector3D( 0.5f,  0.5f,  1.5f), QVector2D(2.0/4.0, 1.0/3.0)}, // v21
            {QVector3D( 0.5f,  0.5f, -1.0f), QVector2D(2.0/4.0, 0)},  // v23
            {QVector3D(-0.5f,  0.5f, -1.0f), QVector2D(1.0/4.0, 0)} // v22
        },

        new GLuint[ind_count] {
            0,  1,  2,  2,  1, 3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  5,  6,  6,  5, 7,      // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  9, 10, 10, 9, 11,      // Face 2 - triangle strip ( v8,  v9, v10, v11)
           12, 13, 14, 14, 13, 15,     // Face 3 - triangle strip (v12, v13, v14, v15)
           16, 17, 18, 18, 19, 16,     // Face 4 - triangle strip (v16, v17, v18, v19)
           20, 21, 22, 22, 23, 20      // Face 5 - triangle strip (v20, v21, v22, v23)
        }
    );

    DetalList.append(RobotAxis4);
    ConnectionPoints.append(QVector3D(0,0,-2.5));
    //вращаем относительно вектора
    //перпедникулярного передней грани третьей  детали
    v1 = RobotAxis3.vertices[2].position; //v2
    v2 = RobotAxis3.vertices[0].position; //0
    v3= RobotAxis3.vertices[3].position; //v3
    RotationAxis.append(QVector3D::normal(v1,v2,v3));
    DetalCount++;

    //ось 5
    vert_count = 24;
    ind_count = 36;
    RbotPart RobotAxis5 =  RbotPart(
        vert_count,
        ind_count,
        new RbotPart::VertexData[vert_count]
        {
            //передняя грань
            {QVector3D(-0.45f, -0.45f,  0.45f), QVector2D(2.0/4.0, 1.0/3.0)},  // v0
            {QVector3D( 0.45f, -0.45f,  0.45f), QVector2D(1.0/4.0, 1.0/3.0)}, // v1
            {QVector3D(-0.45f,  0.45f,  0.45f), QVector2D(2.0/4.0, 2.0/3.0)},  // v2
            {QVector3D( 0.45f,  0.45f,  0.45f), QVector2D(1.0/4.0, 2.0/3.0)}, // v3

            //левая грань
            {QVector3D( 0.45f, -0.45f,  0.45f), QVector2D(1.0/4.0, 1.0/3.0)}, // v4
            {QVector3D( 0.45f, -0.45f, -0.45f), QVector2D(0.0f, 1.0/3.0)}, // v5
            {QVector3D( 0.45f,  0.45f,  0.45f), QVector2D(1.0/4.0, 2.0/3.0)},  // v6
            {QVector3D( 0.45f,  0.45f, -0.45f), QVector2D(0.0f, 2.0/3.0)}, // v7

            //задняя грань
            {QVector3D( 0.45f, -0.45f, -0.45f), QVector2D(1.0f, 1.0/3.0)}, // v8
            {QVector3D(-0.45f, -0.45f, -0.45f), QVector2D(3.0/4.0, 1.0/3.0)},  // v9
            {QVector3D( 0.45f,  0.45f, -0.45f), QVector2D(1.0f, 2.0/3.0)}, // v10
            {QVector3D(-0.45f,  0.45f, -0.45f), QVector2D(3.0/4.0, 2.0/3.0)},  // v11

            //правая грань
            {QVector3D(-0.45f, -0.45f, -0.45f), QVector2D(3.0/4.0, 1.0/3.0)}, // v12
            {QVector3D(-0.45f, -0.45f,  0.45f), QVector2D(2.0/4.0, 1.0/3.0)},  // v13
            {QVector3D(-0.45f,  0.45f, -0.45f), QVector2D(3.0/4.0, 2.0/3.0)}, // v14
            {QVector3D(-0.45f,  0.45f,  0.45f), QVector2D(2.0/4.0, 2.0/3.0)},  // v15

            //нижняя грань
            {QVector3D(-0.45f, -0.45f, -0.45f), QVector2D(2.0/4.0, 1.0f)}, // v16
            {QVector3D( 0.45f, -0.45f, -0.45f), QVector2D(1.0/4.0, 1.0f)}, // v17
            {QVector3D( 0.45f, -0.45f,  0.45f), QVector2D(1.0/4.0, 2.0/3.0)}, // v19
            {QVector3D(-0.45f, -0.45f,  0.45f), QVector2D(2.0/4.0, 2.0/3.0)}, // v18

            //верзняя грань
            {QVector3D(-0.45f,  0.45f,  0.45f), QVector2D(1.0/4.0, 1.0/3.0)}, // v20
            {QVector3D( 0.45f,  0.45f,  0.45f), QVector2D(2.0/4.0, 1.0/3.0)}, // v21
            {QVector3D( 0.45f,  0.45f, -0.45f), QVector2D(2.0/4.0, 0)},  // v23
            {QVector3D(-0.45f,  0.45f, -0.45f), QVector2D(1.0/4.0, 0)} // v22
        },

        new GLuint[ind_count] {
            0,  1,  2,  2,  1, 3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  5,  6,  6,  5, 7,      // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  9, 10, 10, 9, 11,      // Face 2 - triangle strip ( v8,  v9, v10, v11)
           12, 13, 14, 14, 13, 15,     // Face 3 - triangle strip (v12, v13, v14, v15)
           16, 17, 18, 18, 19, 16,     // Face 4 - triangle strip (v16, v17, v18, v19)
           20, 21, 22, 22, 23, 20      // Face 5 - triangle strip (v20, v21, v22, v23)
        }
    );

    DetalList.append(RobotAxis5);
    ConnectionPoints.append(QVector3D(0,0,-1));
    //вращаем относительно вектора
    //перпедникулярного левой грани четветрой детали
    v1 = RobotAxis4.vertices[6].position; //v6
    v2 = RobotAxis4.vertices[4].position; //5
    v3= RobotAxis4.vertices[5].position; //v5
    RotationAxis.append(QVector3D::normal(v1,v2,v3));
    DetalCount++;

    //ось 6
    vert_count = 24;
    ind_count = 36;
    RbotPart RobotAxis6 =  RbotPart(
        vert_count,
        ind_count,
        new RbotPart::VertexData[vert_count]
        {
            //передняя грань
            {QVector3D(-0.35f, -0.35f,  0.25f), QVector2D(2.0/4.0, 1.0/3.0)},  // v0
            {QVector3D( 0.35f, -0.35f,  0.25f), QVector2D(1.0/4.0, 1.0/3.0)}, // v1
            {QVector3D(-0.35f,  0.35f,  0.25f), QVector2D(2.0/4.0, 2.0/3.0)},  // v2
            {QVector3D( 0.35f,  0.35f,  0.25f), QVector2D(1.0/4.0, 2.0/3.0)}, // v3

            //левая грань
            {QVector3D( 0.35f, -0.35f,  0.25f), QVector2D(1.0/4.0, 1.0/3.0)}, // v4
            {QVector3D( 0.35f, -0.35f, -0.25f), QVector2D(0.0f, 1.0/3.0)}, // v5
            {QVector3D( 0.35f,  0.35f,  0.25f), QVector2D(1.0/4.0, 2.0/3.0)},  // v6
            {QVector3D( 0.35f,  0.35f, -0.25f), QVector2D(0.0f, 2.0/3.0)}, // v7

            //задняя грань
            {QVector3D( 0.35f, -0.35f, -0.25f), QVector2D(1.0f, 1.0/3.0)}, // v8
            {QVector3D(-0.35f, -0.35f, -0.25f), QVector2D(3.0/4.0, 1.0/3.0)},  // v9
            {QVector3D( 0.35f,  0.35f, -0.25f), QVector2D(1.0f, 2.0/3.0)}, // v10
            {QVector3D(-0.35f,  0.35f, -0.25f), QVector2D(3.0/4.0, 2.0/3.0)},  // v11

            //правая грань
            {QVector3D(-0.35f, -0.35f, -0.25f), QVector2D(3.0/4.0, 1.0/3.0)}, // v12
            {QVector3D(-0.35f, -0.35f,  0.25f), QVector2D(2.0/4.0, 1.0/3.0)},  // v13
            {QVector3D(-0.35f,  0.35f, -0.25f), QVector2D(3.0/4.0, 2.0/3.0)}, // v14
            {QVector3D(-0.35f,  0.35f,  0.25f), QVector2D(2.0/4.0, 2.0/3.0)},  // v15

            //нижняя грань
            {QVector3D(-0.35f, -0.35f, -0.25f), QVector2D(2.0/4.0, 1.0f)}, // v16
            {QVector3D( 0.35f, -0.35f, -0.25f), QVector2D(1.0/4.0, 1.0f)}, // v17
            {QVector3D( 0.35f, -0.35f,  0.25f), QVector2D(1.0/4.0, 2.0/3.0)}, // v19
            {QVector3D(-0.35f, -0.35f,  0.25f), QVector2D(2.0/4.0, 2.0/3.0)}, // v18

            //верзняя грань
            {QVector3D(-0.35f,  0.35f,  0.25f), QVector2D(1.0/4.0, 1.0/3.0)}, // v20
            {QVector3D( 0.35f,  0.35f,  0.25f), QVector2D(2.0/4.0, 1.0/3.0)}, // v21
            {QVector3D( 0.35f,  0.35f, -0.25f), QVector2D(2.0/4.0, 0)},  // v23
            {QVector3D(-0.35f,  0.35f, -0.25f), QVector2D(1.0/4.0, 0)} // v22
        },

        new GLuint[ind_count] {
            0,  1,  2,  2,  1, 3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  5,  6,  6,  5, 7,      // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  9, 10, 10, 9, 11,      // Face 2 - triangle strip ( v8,  v9, v10, v11)
           12, 13, 14, 14, 13, 15,     // Face 3 - triangle strip (v12, v13, v14, v15)
           16, 17, 18, 18, 19, 16,     // Face 4 - triangle strip (v16, v17, v18, v19)
           20, 21, 22, 22, 23, 20      // Face 5 - triangle strip (v20, v21, v22, v23)
        }
    );

    DetalList.append(RobotAxis6);
    ConnectionPoints.append(QVector3D(0,0,-0.5));
    //вращаем относительно вектора
    //перпедникулярного передней грани пятой
    v1 = RobotAxis4.vertices[2].position; //v2
    v2 = RobotAxis4.vertices[1].position; //1
    v3= RobotAxis4.vertices[0].position; //v0
    RotationAxis.append(QVector3D::normal(v1,v2,v3));
    DetalCount++;
}
