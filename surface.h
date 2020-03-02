#ifndef SURFACE_H
#define SURFACE_H

#include "QVector"
#include "QVector4D"
#include "QGraphicsScene"

class Surface
{
private:
    QVector<QVector4D> nodes;
public:
    Surface(int);
    Surface(QVector<QVector4D>);
    void drawSurface(QGraphicsScene*, float);
    QVector<QVector4D> multiplyMatrix(QVector<QVector4D>);
    Surface rotateOX(float);
    Surface rotateOY(float);
};

#endif // SURFACE_H
