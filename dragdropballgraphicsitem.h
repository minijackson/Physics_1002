#ifndef DRAGDROPBALLGRAPHICSITEM_H
#define DRAGDROPBALLGRAPHICSITEM_H

#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

class DragDropBallGraphicsItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT // Nécéssaire pour les signaux et les slots
public:
    explicit DragDropBallGraphicsItem(qreal height, qreal width, qreal posX = 0, qreal posY = 0,
                                      bool lockX = false, bool lockY = false, QGraphicsItem *parent = 0);
    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal height;
    qreal width;

    bool lockX;
    bool lockY;

    QPointF dragStartPos;

signals:
    void dragStart();
    void dragEnd();
    void dragMove(QPointF variationDistance);

public slots:
    void moveX(int xDistanceVariation);
    void moveY(int yDistanceVariation);
    void moveXY(QPointF xyDistanceVariation);
};

#endif // DRAGDROPBALLGRAPHICSITEM_H
