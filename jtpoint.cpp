#include "jtpoint.h"
#include "QDebug"
//-----------------------------------------------------------------------------
JTPoint::JTPoint(QObject *parent)
    : QObject(parent)
{
    //memset(mPoints, 0, sizeof(mPoints));
}
//-----------------------------------------------------------------------------
JTPoint::JTPoint(const std::array<float, PointCount>& points, QObject *parent)
    : QObject(parent)
    , mPoints(points)
{
}
//-----------------------------------------------------------------------------
JTPoint::JTPoint(const JTPoint& other)
    : QObject(other.parent())
    , mPoints(other.mPoints)
{
}
//-----------------------------------------------------------------------------
JTPoint& JTPoint::operator=(const JTPoint& other)
{
    if (this != &other) {
        setParent(other.parent());
        setPoints(other.mPoints);
    }
    return *this;
}
//-----------------------------------------------------------------------------
void JTPoint::setPoint(int index, float value)
{
    if (!isValidIndex(index)) {
        qWarning() << "JTPoint::setPoint: Invalid index" << index;
        return;
    }
    if (!qFuzzyCompare(mPoints[index], value)) {
        mPoints[index] = value;
    }
}
//-----------------------------------------------------------------------------
float JTPoint::at(int index) const
{
    if (!isValidIndex(index)) {
        qWarning() << "JTPoint::at: Invalid index" << index;
        return 0.0f;
    }
    return mPoints[index];
}
//-----------------------------------------------------------------------------
float& JTPoint::operator[](int index)
{
    Q_ASSERT_X(isValidIndex(index),
               "JTPoint::operator[]",
               "Index out of bounds");
    return mPoints[index];
}
//-----------------------------------------------------------------------------
const float& JTPoint::operator[](int index) const
{
    Q_ASSERT_X(isValidIndex(index),
               "JTPoint::operator[] const",
               "Index out of bounds");
    return mPoints[index];
}
//-----------------------------------------------------------------------------
void JTPoint::setPoints(const std::array<float, PointCount>& points)
{
    if (mPoints == points) {
        return;
    }

    bool changed = false;
    for (int i = 0; i < PointCount; ++i) {
        if (!qFuzzyCompare(mPoints[i], points[i])) {
            mPoints[i] = points[i];
            changed = true;
        }
    }
}
//-----------------------------------------------------------------------------
bool JTPoint::equals(const JTPoint &pt1, const  JTPoint &pt2, float acc)
{
    bool equal = true;
    if (pt1.size() == pt2.size()) {
        for (int i = 0; i < pt1.size(); i++)
        {
            if ((pt1.points()[i] < pt2.points()[i] - acc) || (pt1.points()[i] > pt2.points()[i] + acc)) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}
