#include "fallingobjectmdisubwindow.h"

FallingObjectMdiSubWindow::FallingObjectMdiSubWindow(QWidget *parent) :
    QMdiSubWindow(parent)
{
    this->setWindowTitle("Objet tombant");

    balle = new FallingBallGraphicsItem(10, 250, 10, 10, 500);

    graphicsScene = new QGraphicsScene(this);
    graphicsScene->addItem(balle);
    graphicsView = new QGraphicsView(graphicsScene);
//    graphicsView->setGeometry(0,0,550,550);
//    graphicsView->setFixedSize(550,550);


    this->setGeometry(0,0,600,600);
    this->setWidget(graphicsView);
}

void FallingObjectMdiSubWindow::activateAnimation() {
    balle->activateAnimation();
}
