#include "dragdropballgraphicsitem.h"

DragDropBallGraphicsItem::DragDropBallGraphicsItem(qreal height, qreal width, qreal posX, qreal posY,
                                                   bool lockX, bool lockY, QGraphicsItem *parent) :
    QGraphicsEllipseItem(posX, posY, width, height, parent),
    height(height), width(width), lockX(lockX), lockY(lockY)
{
    setCursor(Qt::OpenHandCursor);
}

void DragDropBallGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);

    setCursor(Qt::ClosedHandCursor);
    dragStartPos = this->pos();
    emit dragStart();
}

void DragDropBallGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);

    setCursor(Qt::OpenHandCursor);
    emit dragEnd();
}

void DragDropBallGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
             .length() < QApplication::startDragDistance()) {
             return;
    }

    QPointF newPos = this->dragStartPos + event->scenePos() - event->buttonDownScenePos(Qt::LeftButton);
    QPointF distanceVariation = event->pos() - event->lastPos();

    if(!(lockX || lockY))
        this->setPos(newPos);
    else if(lockX && !lockY) {
        distanceVariation.setX(0);
        newPos.setX(dragStartPos.x());
        this->setPos(newPos);
    } else if(!lockX && lockY) {
        distanceVariation.setY(0);
        newPos.setY(dragStartPos.y());
        this->setPos(newPos);
    }
    emit dragMove(distanceVariation);
}

void DragDropBallGraphicsItem::moveX(int xDistanceVariation) {
    setPos(x() + xDistanceVariation, y());
}

void DragDropBallGraphicsItem::moveY(int yDistanceVariation) {
    setPos(x(), y() + yDistanceVariation);
}

void DragDropBallGraphicsItem::moveXY(QPointF xyDistanceVariation) {
    setPos(pos() + xyDistanceVariation);
}
