#ifndef JTPOINT_H
#define JTPOINT_H

#include <QObject>
#include "math.h"

class JTPoint : public QObject
{
    Q_OBJECT

    public:
        static constexpr int PointCount = 6;

        // Конструкторы
        explicit JTPoint(QObject *parent = nullptr);
        explicit JTPoint(const std::array<float, PointCount>& points,
                         QObject *parent = nullptr);

        JTPoint(const JTPoint& other); // Конструктор копирования
        JTPoint& operator=(const JTPoint& other); // Оператор присваивания
        //JTPoint(JTPoint&& other) = delete; // QObject не поддерживает перемещение
        JTPoint& operator=(JTPoint&& other) = delete;

        // Методы установки значений с сигналами
        void setA1(float a) {mPoints[0] = a;}
        void setA2(float a) {mPoints[1] = a;}
        void setA3(float a) {mPoints[2] = a;}
        void setA4(float a) {mPoints[3] = a;}
        void setA5(float a) {mPoints[4] = a;}
        void setA6(float a) {mPoints[5] = a;}

        void setA1Rad(float a) {mPoints[0] = a * 180.f / M_PI;}
        void setA2Rad(float a) {mPoints[1] = a * 180.f / M_PI;}
        void setA3Rad(float a) {mPoints[2] = a * 180.f / M_PI;}
        void setA4Rad(float a) {mPoints[3] = a * 180.f / M_PI;}
        void setA5Rad(float a) {mPoints[4] = a * 180.f / M_PI;}
        void setA6Rad(float a) {mPoints[5] = a * 180.f / M_PI;}

        void setPoint(int index, float value);

        // Методы получения значений
        float a1() const { return mPoints[0]; }
        float a2() const { return mPoints[1]; }
        float a3() const { return mPoints[2]; }
        float a4() const { return mPoints[3]; }
        float a5() const { return mPoints[4]; }
        float a6() const { return mPoints[5]; }

        float a1rad() const { return mPoints[0] * static_cast<float>(M_PI) / 180.0f; }
        float a2rad() const { return mPoints[1] * static_cast<float>(M_PI) / 180.0f; }
        float a3rad() const { return mPoints[2] * static_cast<float>(M_PI) / 180.0f; }
        float a4rad() const { return mPoints[3] * static_cast<float>(M_PI) / 180.0f; }
        float a5rad() const { return mPoints[4] * static_cast<float>(M_PI) / 180.0f; }
        float a6rad() const { return mPoints[5] * static_cast<float>(M_PI) / 180.0f; }

        // Безопасный доступ к элементам
        float at(int index) const;
        float& operator[](int index);
        const float& operator[](int index) const;

        // Утилиты
        int size() const { return PointCount; }
        bool isValidIndex(int index) const {
            return index >= 0 && index < PointCount;
        }

        // Работа со всеми точками
        std::array<float, PointCount> points() const { return mPoints; }
        void setPoints(const std::array<float, PointCount>& points);

private:
    std::array<float, PointCount> mPoints{};

};

#endif // JTPOINT_H
