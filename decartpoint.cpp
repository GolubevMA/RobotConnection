#include "decartpoint.h"
#include "qdebug.h"
//-----------------------------------------------------------------------------
DecartPoint::DecartPoint(QObject *parent, int coord_type) : QObject(parent), mCoordType(coord_type)
{}
//-----------------------------------------------------------------------------
DecartPoint::DecartPoint(int CoordTYpe, const std::array<float, CoordCount>& points,QObject *parent)
    :QObject (parent),
        mCoordType(CoordTYpe),
        mCoords(points)
{}
//-----------------------------------------------------------------------------
DecartPoint::DecartPoint(const DecartPoint& other)
    : QObject(other.parent()),
        mCoordType(other.mCoordType),
        mCoords(other.mCoords)
{}
//-----------------------------------------------------------------------------
DecartPoint& DecartPoint::operator=(const DecartPoint& other)
{
    if (this != &other)
    {
        setParent(other.parent());
        setType(other.mCoordType);
        setPoints(other.mCoords);
    }
    return *this;
}
//-----------------------------------------------------------------------------
void DecartPoint::setPoint(int index, float value)
{
    if (!isValidIndex(index)) {
         qWarning() << "JTPoint::setPoint: Invalid index" << index;
        return;
 }
    if (!qFuzzyCompare(mCoords[index], value)) {
         mCoords[index] = value;
    }
}
//-----------------------------------------------------------------------------
float DecartPoint::at(int index) const
{
 if (!isValidIndex(index)) {
     qWarning() << "JTPoint::at: Invalid index" << index;
     return 0.0f;
 }
 return mCoords[index];
}
//-----------------------------------------------------------------------------
float& DecartPoint::operator[](int index)
{
 Q_ASSERT_X(isValidIndex(index),
            "JTPoint::operator[]",
            "Index out of bounds");
 return mCoords[index];
}
//-----------------------------------------------------------------------------
const float& DecartPoint::operator[](int index) const
{
    Q_ASSERT_X(isValidIndex(index),
            "JTPoint::operator[] const",
            "Index out of bounds");
    return mCoords[index];
}
//-----------------------------------------------------------------------------
void DecartPoint::setPoints(const std::array<float, CoordCount>& points)
{
 if (mCoords == points) {
     return;
 }
 bool changed = false;
 for (int i = 0; i < CoordCount; ++i) {
     if (!qFuzzyCompare(mCoords[i], points[i])) {
         mCoords[i] = points[i];
         changed = true;
     }
  }
}
