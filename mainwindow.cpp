#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QGraphicsScene"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Surface MainWindow::createSurface() {

    QVector<QVector4D> pts;

    ui->graphicsView->items().clear();
    ui->graphicsView->scene()->clear();

    QVector4D temp1(ui->X1->value(), ui->Y1->value(),ui->Z1->value(), 1);
    QVector4D temp2(ui->X2->value(), ui->Y2->value(),ui->Z2->value(), 1);
    QVector4D temp3(ui->X3->value(), ui->Y3->value(),ui->Z3->value(), 1);
    QVector4D temp4(ui->X4->value(), ui->Y4->value(),ui->Z4->value(), 1);

    pts.push_back(temp1);
    pts.push_back(temp2);
    pts.push_back(temp3);
    pts.push_back(temp4);

    Surface surface(pts);

    // Нанесение осей координат
    ui->graphicsView->scene()->addLine(-200, 0, 200, 0, QPen(Qt::red));
    ui->graphicsView->scene()->addLine(0, -200, 0, 200, QPen(Qt::red));

    return surface;

}

void MainWindow::on_rotateOX_clicked() {

    Surface surface = createSurface();

    Surface rotateSurface = surface.rotateOX(ui->angle->value());
    rotateSurface.drawSurface(ui->graphicsView->scene(), ui->accuracy->value());

}

void MainWindow::on_rotateOY_clicked() {

    Surface surface = createSurface();

    Surface rotateSurface = surface.rotateOY(ui->angle->value());
    rotateSurface.drawSurface(ui->graphicsView->scene(), ui->accuracy->value());

}

void MainWindow::on_drawSurface_clicked() {

    Surface surface = createSurface();
    surface.drawSurface(ui->graphicsView->scene(), ui->accuracy->value());

}
