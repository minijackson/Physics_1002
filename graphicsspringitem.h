#ifndef GRAPHICSSPRINGITEM_H
#define GRAPHICSSPRINGITEM_H

#include <cmath>

#include <QGraphicsItem>
#include <QVector>
#include <QPainter>
#include <QColor>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

class GraphicsSpringItem : public QObject, public QGraphicsItem
{
    Q_OBJECT // Nécéssaire pour les signaux et les slots
public:
    explicit GraphicsSpringItem(int height, int width, int numberOfDiagonal = 10,
                                float springConstant = 0.5, int objectMass = 5, float frictionConstant = 0,
                                QColor strokeColor = Qt::black, QGraphicsItem *parent = 0);
    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;

signals:
    void springGeometryAnimationChange(int);

public slots:
    void stopAnimation();
    void startAnimation();
    void updateSpring(QPointF variationDistance);
    void animationFrame(int frame);

    void setSpringConstant(float springConstant);
    void setSpringConstant(double springConstant);
    void setFrictionConstant(float frictionConstant);
    void setFrictionConstant(double frictionConstant);
    void setObjectMass(float objectMass);
    void setObjectMass(double objectMass);

protected:
    int height;
    int width;
    int initialWidth;
    int releaseWidth;

    int numberOfDiagonalDots;

    float oscillationPeriod;
    float springConstant;
    int objectMass;
    float frictionConstant;

    QColor strokeColor;
    bool animated;

    QTimeLine *timeLine;
    int animationDuration;
    QVector<int> animationFramesWidths;

    void calcAnimation();
};

#endif // GRAPHICSSPRINGITEM_H
