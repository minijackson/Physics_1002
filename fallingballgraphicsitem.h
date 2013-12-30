#ifndef FALLINGBALLGRAPHICSITEM_H
#define FALLINGBALLGRAPHICSITEM_H

#include <QApplication>

#include <QTimeLine>
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>

#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QMimeData>

class FallingBallGraphicsItem : public QGraphicsEllipseItem
{
public:
    explicit FallingBallGraphicsItem(qreal posX, qreal posY, qreal ballWidth, qreal ballHeight, int windowHeight);

public slots:
    void activateAnimation();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:

    QTimeLine *timeLine;
    QGraphicsItemAnimation *animation;

    qreal height;
    qreal width;

    qreal windowHeight;

    QPointF dragStartPos;

    int animationDuration;

    void calcAnimation();
};

#endif // FALLINGBALLGRAPHICSITEM_H
