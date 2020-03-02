#include "surface.h"
#include "QtMath"

Surface::Surface(int num) {

    QVector4D temp(0, 0, 0, 0);

    for (int i = 0; i < num; ++i)

        nodes.push_back(temp);

}

Surface::Surface(QVector<QVector4D> pts) {

    nodes = pts;

}

QVector4D multiplyMatrixOnConst(QVector4D matrix, float num) {

    QVector4D res;

    res.setX(matrix.x() * num);
    res.setY(matrix.y() * num);
    res.setZ(matrix.z() * num);
    res.setW(1);

    return res;

}

QVector4D additionMatrix(QVector<QVector4D> matrices) {

    QVector4D res;

    for (int i = 0; i < matrices.size(); ++i) {

        res.setX(res.x() + matrices[i].x());
        res.setY(res.y() + matrices[i].y());
        res.setZ(res.z() + matrices[i].z());
        res.setW(1);

    }

    return res;

}

void Surface::drawSurface(QGraphicsScene* scene, float step) {

    QVector<QVector<QVector4D>> surfaceNodes;

    QVector<QVector4D> newLine;

    int numOfLines = -1;

    for (float u = 0; u <= 1; u += step) {

        surfaceNodes.push_back(newLine);
        numOfLines++;

        for (float w = 0; w <= 1; w += step) {

            QVector<QVector4D> tempNodes;

            QVector4D temp1 = multiplyMatrixOnConst(nodes[0], (1 - u) * (1 - w));
            QVector4D temp2 = multiplyMatrixOnConst(nodes[1], (1 - u) * w);
            QVector4D temp3 = multiplyMatrixOnConst(nodes[2], u * (1 - w));
            QVector4D temp4 = multiplyMatrixOnConst(nodes[3], u * w);

            tempNodes.push_back(temp1);
            tempNodes.push_back(temp2);
            tempNodes.push_back(temp3);
            tempNodes.push_back(temp4);

            QVector4D newNode = additionMatrix(tempNodes);
            surfaceNodes[numOfLines].push_back(newNode);

        }

    }

    for (int i = 0; i < surfaceNodes.size(); ++i) {

        for (int n = 0; n < surfaceNodes[i].size(); ++n) {

            if (n < surfaceNodes[i].size() - 1)
                scene->addLine(surfaceNodes[i][n].x(), surfaceNodes[i][n].y(), surfaceNodes[i][n+1].x(), surfaceNodes[i][n+1].y());

            if (i < surfaceNodes.size() - 1)
                scene->addLine(surfaceNodes[i][n].x(), surfaceNodes[i][n].y(), surfaceNodes[i+1][n].x(), surfaceNodes[i+1][n].y());

        }

    }

}

QVector<QVector4D> Surface::multiplyMatrix(QVector<QVector4D> mR) {

    QVector<QVector4D> res;

    QVector4D temp(0, 0, 0, 0);

    for(int i = 0; i < nodes.size(); ++i)
        res.push_back(temp);

    for(int i = 0; i < nodes.size(); ++i) {

        res[i].setX(nodes[i].x() * mR[0].x() + nodes[i].y() * mR[1].x() + nodes[i].z() * mR[2].x() + nodes[i].w() * mR[3].x());
        res[i].setY(nodes[i].x() * mR[0].y() + nodes[i].y() * mR[1].y() + nodes[i].z() * mR[2].y() + nodes[i].w() * mR[3].y());
        res[i].setZ(nodes[i].x() * mR[0].z() + nodes[i].y() * mR[1].z() + nodes[i].z() * mR[2].z() + nodes[i].w() * mR[3].z());
        res[i].setW(nodes[i].x() * mR[0].w() + nodes[i].y() * mR[1].w() + nodes[i].z() * mR[2].w() + nodes[i].w() * mR[3].w());

    }

    return res;

}

Surface Surface::rotateOX(float angle) {

    QVector<QVector4D> tempMatrix;
    QVector<QVector4D> matrixRotation;

    float radAngle = qDegreesToRadians(angle);

    matrixRotation.push_back(QVector4D(1, 0, 0, 0));
    matrixRotation.push_back(QVector4D(0, cos(radAngle), sin(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, -sin(radAngle), cos(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, 0, 0, 1));

    tempMatrix = multiplyMatrix(matrixRotation);
    Surface res(tempMatrix);

    return res;

}

Surface Surface::rotateOY(float angle) {

    QVector<QVector4D> tempMatrix;
    QVector<QVector4D> matrixRotation;

    float radAngle = qDegreesToRadians(angle);

    matrixRotation.push_back(QVector4D(cos(radAngle), 0, -sin(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, 1, 0, 0));
    matrixRotation.push_back(QVector4D(sin(radAngle), 0, cos(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, 0, 0, 1));

    tempMatrix = multiplyMatrix(matrixRotation);
    Surface res(tempMatrix);

    return res;

}
