#ifndef TROBOTWIDGET_H
#define TROBOTWIDGET_H

#include <QWidget>
#include <QtOpenGl/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtGui>
#include <QOpenGLContext>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include "vars.h"
#include "trobotmodel.h"



class TRobotWidget : public QGLWidget
{
    Q_OBJECT
public:

    explicit TRobotWidget(QWidget *parent = nullptr);
    ~TRobotWidget();

    void SetPlane(int plane);
    void SetRobotModel(TRobotModel *model);
    void SetRobotRotation(float *angles, int ang_count);
    void SetTexture(QString path);

    void initShaders();
    void LoadCubeTexture();
    void initTexure();
    void drawRobot(QMatrix4x4 matrx, QMatrix4x4 &projection);


    void resizeGL(int w, int h) override;
    void initializeGL() override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:

    struct
    {
        float verticalAngle;
        float aspectRatio;
        float nearPlane;
        float farPlane;
    } mPerspective;

    struct
    {
        QVector3D eye;
        QVector3D center;
        QVector3D up;
    } mLookAt;

    TRobotModel *CurrentModel; //моедль отрисоываемого робота

    //квантерионы поворта деталей робота
    QVector<QQuaternion> rotations;

    //(в дпъльанешем избавимся либо от tex path, либо от texIMge
    //(елси дальше размещать элменты в stck widget - то при загрзку карты (слоя)
    // мы будем создавть ноые элменты со статчиеской текурурой и грузить их в stack widgte)

    QString mTexturePath;                                           //путь к  директроям текстуры
    QImage mTexImage;                                               //изображение текущей текстуры
    bool mTexChanged;                                               //флаг изменения текутры

    QOpenGLTexture  *texture;                                       //текстура кубмапап
    GLuint          hdTexture;                                       //хендл текстуры

    QQuaternion Rotate;                                             //кватернион поврота
    QList<QOpenGLBuffer> arrayBufs;
    //QMatrix4x4      mViewMat;                                          //матрица камеры (полдение камаеры в простнстве, угол поворита камеры)
    //QMatrix4x4      mProjectionMat;                                    //матрица перспектинвой проэкции облсасти отрисовки

    QGLShaderProgram tex_ShaderProg;								// программа шейдеров стандартного вывода текстуры
    int				 tex_Vertexes;									// атрибуы стандартного шейдера
    int				 tex_TexCoord;


    bool mouseGrabFlag;                                             //флаг зазвата (активируем вращение при перемещнии курсора)
    QPoint  LastPoint;
    float  LastAngleX;                                              //последний угол
    float  LastAngleY;                                              //последний угол


    bool  clear_flag;												// флаг рисования пустого окна - нужен при первом включении, пока считаются лучи
};

#endif // TROBOTWIDGET_H
