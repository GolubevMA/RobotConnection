#include "trobotwidget.h"
    //------------------------------------------------------------------------------
const QString mBackImagePath = "img/back.png";
const QString mRightImagePath = "img/right.png";
const QString mLeftImagePath =  "img/left.png";
const QString mTopImagePath = "img/top.png";
const QString mBottomImagePath = "img/bottom.png";
const QString mFrontImagePath = "img/font.png";
//------------------------------------------------------------------------------
TRobotWidget::TRobotWidget(QWidget *parent) : QGLWidget(parent)
{
    mTexturePath =  ":/img/Bskybox.png";
    mTexChanged = false;
    mTexImage = QImage(mTexturePath).mirrored();
    texture = NULL;

    //определим парамтеры пртрици пердставления
    mLookAt.eye =    {0.0f, 0.0f, 0.0f};
    mLookAt.center = {0.0f, 0.0f, -1.0f};
    mLookAt.up =     {0.0f, 1.0f, 0.0f};

    qreal aspect = qreal(width()) / qreal(height() ? height() : 1);
    const qreal zNear = 0.1, zFar = 100.0, fov = 60.0;

    //утснавливаем парматреы облсти отрсивки
    mPerspective.verticalAngle = fov;
    mPerspective.farPlane = zFar;
    mPerspective.nearPlane = zNear;
    mPerspective.aspectRatio = aspect;

    Rotate = QQuaternion();
    rotations.clear();

    mouseGrabFlag = false;
    LastAngleX = 0;
    LastAngleY = 0;

    setFocus();
}
//------------------------------------------------------------------------------
TRobotWidget::~TRobotWidget()
{
    foreach (QOpenGLBuffer buf, arrayBufs) {
        buf.destroy();
    }
    delete texture;
}
//------------------------------------------------------------------------------
//устанивливаем  геомтрическую модель робота
//------------------------------------------------------------------------------
void TRobotWidget::SetRobotModel(TRobotModel *model)
{
    CurrentModel = model;
    for (int i = 0; i < CurrentModel->DetalCount; i++) {
        rotations.append(QQuaternion());
    }
}
//------------------------------------------------------------------------------
void TRobotWidget::SetPlane(int plane) {
    switch (plane)
    {
        //XZ
        case 0:
        {
            QVector3D AxisX = QVector3D(0, 0, 1);
            //стчиаем кватериан как произведение кватерианов
            //поворта вокруг каждых осей //вращаем
            QQuaternion rotate_y = QQuaternion::fromAxisAndAngle(AxisX, -M_PI / 2);
            Rotate = rotate_y;
            updateGL();
        }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}
//------------------------------------------------------------------------------
// вращаем оси робота
//------------------------------------------------------------------------------
void TRobotWidget::SetRobotRotation(float *angles, int ang_count)
{
    if (ang_count > CurrentModel->DetalCount) ang_count = CurrentModel->DetalCount;
    rotations.clear();


    //фоирмуем  список квартенинов поврота вокрук каждой оси на каждый угол
    for (int i = 0; i < ang_count; i++) {
        rotations.append(QQuaternion::fromAxisAndAngle(CurrentModel->RotationAxis[i], angles[i]));
    }
    updateGL();
}
//------------------------------------------------------------------------------
void TRobotWidget::SetTexture(QString path)
{
    //загрузим изображене из указанного файла
    mTexturePath = path;
    mTexImage = QImage(path).mirrored();
    mTexChanged = true;
    qDebug() << "path " << path;
}
//------------------------------------------------------------------------------
//колмиплируем и биндим шейдеры
//------------------------------------------------------------------------------
void TRobotWidget::initShaders()
{
    //компилируем вершинные шейдер
    if (!tex_ShaderProg.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();

    //компилириуем фрагментный шейдер
    if (!tex_ShaderProg.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    //линкуем шейдеры
    if (!tex_ShaderProg.link())
        close();

    //биндим шейдеры
    if (!tex_ShaderProg.bind())
        close();
}
//------------------------------------------------------------------------------
//загружаем стандартную текстуру
//------------------------------------------------------------------------------
void TRobotWidget::initTexure()
{
    texture = new QOpenGLTexture(mTexImage/*QImage(mTexturePath).mirrored()*/);

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//------------------------------------------------------------------------------
//загружаем стандартную текууру для скайбокса
//------------------------------------------------------------------------------
void TRobotWidget::LoadCubeTexture()
{
    const int width = 100;
    const int height = 100;

    QImage posx = QImage(width, height, QImage::Format_RGBA8888);
    posx.fill(Qt::blue);
    QImage negx = QImage(width, height, QImage::Format_RGBA8888);
    negx.fill(Qt::green);

    QImage posy = QImage(width, height, QImage::Format_RGB32);
    posy.fill(Qt::red);
    QImage negy = QImage(width, height, QImage::Format_RGB32);
    negy.fill(Qt::green);

    QImage posz = QImage(width, height, QImage::Format_RGB32);
    posz.fill(Qt::green);
    QImage negz = QImage(width, height, QImage::Format_RGB32);
    negz.fill(Qt::green);

    uchar data[width][height];
    memset(data, 0x355E3B, sizeof(data));

    //создаем тестуру в видеопамяти
    glGenTextures(1, &hdTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, hdTexture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //гризми тексутуру для каждой из шести гранией куба
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posx.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posy.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, negy.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posz.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, negz.constBits());

}
//------------------------------------------------------------------------------
//процедура отрисовки робота по модели
//------------------------------------------------------------------------------
void TRobotWidget::drawRobot(QMatrix4x4 matrx, QMatrix4x4 &projection)
{
    //прохоимся по всем деталям
    for (int i = 0; i < CurrentModel->DetalCount; i++)
    {
        RbotPart &part  = CurrentModel->DetalList[i];
        //буффер точек соответкующей детали
        QVector3D &pos = CurrentModel->ConnectionPoints[i];

        //копруем матрицу смщенения камеры
        //QMatrix4x4 mt = matrx;
        //позиционируем  текущкю деталь относиетлльно установленного смщеенения камеры
        matrx.translate(pos);
        //вращем деталь на соответсвующий угол
        if (!rotations.isEmpty()) matrx.rotate(rotations[i]);

        //загруем матрцу проэкуций
        tex_ShaderProg.setUniformValue("mvp_matrix", projection * matrx);
        tex_ShaderProg.setUniformValue("texture", 0);

        //загрузим массив координат детали
        quintptr offset = 0;
        arrayBufs[i].bind();

        int vertexLocation = tex_ShaderProg.attributeLocation("a_position");
        tex_ShaderProg.enableAttributeArray(vertexLocation);
        tex_ShaderProg.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(RbotPart::VertexData));

        //определяем текутурные координаты
        offset += sizeof(QVector3D);

        int texcoordLocation = tex_ShaderProg.attributeLocation("a_texcoord");
        tex_ShaderProg.enableAttributeArray(texcoordLocation);
        tex_ShaderProg.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(RbotPart::VertexData));

        //отрисывавам фигуруу
        glDrawElements(GL_TRIANGLES, part.IndexCount, GL_UNSIGNED_INT, part.indexes);      //indexes.constData());

        arrayBufs[i].release();
    }
}
//------------------------------------------------------------------------------
//инициализируем фугкиции opnenGl,
//создаем  обьекты класса геометрических памрамтеров,
// компилируем шейдерные прогрмммы
//------------------------------------------------------------------------------
void TRobotWidget::initializeGL()
{
    QGLFunctions *f = context()->functions();
    f->initializeGLFunctions();

    glClearColor(0.3, 0.5, 0.6, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    //создадим тесктуру
    initTexure();

    //иницииализируем буффер вершин всех примитиовов
    foreach (RbotPart axis, CurrentModel->DetalList)
    {
        QOpenGLBuffer buf;
        buf.create();
        buf.bind();
        buf.allocate(axis.vertices, axis.PointCount * sizeof(RbotPart::VertexData));
        buf.release();
        arrayBufs.append(buf);
    }
}
//------------------------------------------------------------------------------
void TRobotWidget::resizeGL(int w, int h)
{
    //обновляем размеры канвы
    glViewport(0,0, w, h);

    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.5, zFar = 100.0, fov = 60.0;

    //утснавливаем парматреы облсти отрсивки
    mPerspective.verticalAngle = fov;
    mPerspective.farPlane = zFar;
    mPerspective.nearPlane = zNear;
    mPerspective.aspectRatio = aspect;

    updateGL();
}
//------------------------------------------------------------------------------
void TRobotWidget::paintGL()
{
    makeCurrent();

    QGLFunctions *f = context()->functions();

    // очщаем буфферы
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);


    //если стотит флаг обновления тексуры - зграузим новую текстуру в динмаическую память
    if (mTexChanged)
    {
        mTexChanged = false;
        delete texture;
        texture = NULL;
        initTexure();
    }
    texture->bind(0);
    f->glActiveTexture(GL_TEXTURE0);

    //определяем поворот и смещение камеры
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(0.0, -3.0, -7.0);
    matrix.rotate(Rotate);

    //обновляем парметры перспективной матрицы
    QMatrix4x4 mProjectionMat;
    mProjectionMat.setToIdentity();
    mProjectionMat.perspective(mPerspective.verticalAngle,
       mPerspective.aspectRatio,
       mPerspective.nearPlane,
       mPerspective.farPlane);

    //конфигурируем мтрицу видового предсатнвления
    //на основе позиции камеры и угла поворота
//    QMatrix4x4 matrix;
//    matrix.setToIdentity();
//    matrix.lookAt(mLookAt.eye,
//        mLookAt.center,
//        mLookAt.up);

    drawRobot(matrix, mProjectionMat);

    texture->release();
}
//------------------------------------------------------------------------------
void TRobotWidget::mousePressEvent(QMouseEvent *event)
{    
    LastPoint = event->pos();
    event->accept();
}
//------------------------------------------------------------------------------
void TRobotWidget::mouseMoveEvent(QMouseEvent *event)
{
    LastAngleX += 1 / M_PI * (event->pos().y() - LastPoint.y());
    LastAngleY += 1 / M_PI * (event->pos().x() - LastPoint.x());

    QVector3D AxisX = QVector3D(1, 0, 0);
    QVector3D AxisY = QVector3D(0, 1, 0);

    //стчиаем кватериан как произведение кватерианов
    //поворта вокруг каждых осей
    //вращем камеру вокруг оси X и У по часовой стрелке
    QQuaternion rotate_y = QQuaternion::fromAxisAndAngle(AxisY, LastAngleY);
    QQuaternion rotate_x = QQuaternion::fromAxisAndAngle(AxisX, LastAngleX);
    Rotate = rotate_x * rotate_y;

    LastPoint = event->pos();
//    //рассичтаем параматреы видовой матрицы
//    QMatrix4x4 mat;
//    mat.setToIdentity();
//    mat.rotate(rotate_x);
//    mat.rotate(rotate_y);
    //mLookAt.center = {0.0f, 0.0f, -5.0f};
    //mLookAt.center = mLookAt.center * mat;
    updateGL();
}
//------------------------------------------------------------------------------
void TRobotWidget::keyPressEvent(QKeyEvent *event)
{
    event->accept();

    //вращем камеру вокруг оси X по часовой стрелке
    int dir = 1;
    static float angle = 0.0;

    if (event->key() == Qt::Key_F5){
        dir = 1;
    }
    else if (event->key() == Qt::Key_F6) {
        dir = -1;
    }
    else return;

    QVector3D AxisX = QVector3D(1, 0, 0);
    QVector3D AxisY = QVector3D(0, 1, 0);
    angle += 1 / M_PI * (10*dir);

    //считаем кватерион повората
    QQuaternion rotate_Y = QQuaternion::fromAxisAndAngle(AxisY, angle);
    QQuaternion rotate_X = QQuaternion::fromAxisAndAngle(AxisX, angle);
    Rotate = rotate_X * rotate_Y;

//    //рассичтаем параматреы видовой матрицы
//    QMatrix4x4 mat;
//    mat.setToIdentity();
//    mat.rotate(rotate_Y);
//    mat.rotate(rotate_X);
//    mLookAt.center = {0.0f, 0.0f, -1.0f};
//    mLookAt.center = mLookAt.center * mat;

    updateGL();
}
//------------------------------------------------------------------------------
void TRobotWidget::wheelEvent(QWheelEvent *event)
{
    float delta = event->delta() > 0 ? -5.0f : +5.0f;
    mPerspective.verticalAngle += delta;

    updateGL();
}
//------------------------------------------------------------------------------


