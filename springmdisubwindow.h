#ifndef SPRINGMDISUBWINDOW_H
#define SPRINGMDISUBWINDOW_H

#include "graphicsspringitem.h"
#include "dragdropballgraphicsitem.h"

#include <QMdiSubWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class SpringMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit SpringMdiSubWindow(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;

    GraphicsSpringItem *spring;
    DragDropBallGraphicsItem *ball;
};

#endif // SPRINGMDISUBWINDOW_H
