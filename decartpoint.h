#ifndef DECARTPOINT_H
#define DECARTPOINT_H

#include <QObject>
#include "math.h"

class DecartPoint : public QObject
{
    Q_OBJECT
public:

    //чило координат
    static constexpr int CoordCount = 6;

    //тип точки в декартвоой систмеме координат
    // 0 - точка задает положение схвата робота через напрявляющие косинусы
    // 1 - положение схвата задется углами эйлера
    enum CoordType {DiretCos, EulerAngles};

    // Конструкторы
    explicit DecartPoint(QObject *parent = nullptr, int CoordTYpe = DiretCos);
    explicit DecartPoint(int CoordTYpe , const std::array<float, CoordCount>& points,
                     QObject *parent = nullptr);

    DecartPoint(const DecartPoint& other); // Конструктор копирования
    DecartPoint& operator=(const DecartPoint& other); // Оператор присваивания
    DecartPoint& operator=(DecartPoint&& other) = delete;

    //устновка координат
    void setX(float x) {mCoords[0] = x;}
    void setY(float y) {mCoords[1] = y;}
    void setZ(float z) {mCoords[2] = z;}

    //установка углов Эйлера / напрявляющих косинусов
    void setO(float o) {mCoords[3] = o;}
    void setA(float a) {mCoords[4] = a;}
    void setT(float t) {mCoords[5] = t;}

    void setXyz(QVector3D &xyz);

    void setPoint(int index, float value);
    void setType(int type) {mCoordType = type;}

    // Методы получения значений
    float x() const { return mCoords[0]; }
    float y() const { return mCoords[1]; }
    float z() const { return mCoords[2]; }

    float o() const { return mCoords[3];}
    float a() const { return mCoords[4]; }
    float t() const { return mCoords[5]; }     

    float oRad() const { return mCoords[3] * M_PI / 180;}
    float aRad() const { return mCoords[4] * M_PI / 180; }
    float tRad() const { return mCoords[5] * M_PI / 180; }

    QVector3D xyz();

    int type() {return mCoordType;}

    // Безопасный доступ к элементам
    float at(int index) const;
    float& operator[](int index);
    const float& operator[](int index) const;

    // Утилиты
    int size() const { return CoordCount; }
    bool isValidIndex(int index) const {
        return index >= 0 && index < CoordCount;
    }
    //std::array<float, PointCount> points() const { return mPoints; }
    void setPoints(const std::array<float, CoordCount>& points);

private:

    //тип координаты
    int mCoordType;

    //массив точек
    std::array<float, CoordCount> mCoords{};
};

#endif // DECARTPOINT_H
