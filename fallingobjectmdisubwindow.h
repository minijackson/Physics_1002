#ifndef FALLINGOBJECTMDISUBWINDOW_H
#define FALLINGOBJECTMDISUBWINDOW_H

#include "fallingballgraphicsitem.h"

#include <QMdiSubWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class FallingObjectMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit FallingObjectMdiSubWindow(QWidget *parent = 0);

public slots:
    void activateAnimation();

private:
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;

    FallingBallGraphicsItem *balle;
};

#endif // FALLINGOBJECTMDISUBWINDOW_H
