#include "graphicsspringitem.h"

#include <iostream>

GraphicsSpringItem::GraphicsSpringItem(int height, int width, int numberOfDiagonalDots,
                                       float springConstant, int objectMass, float frictionConstant,
                                       QColor strokeColor, QGraphicsItem *parent) :
    height(height), width(width), initialWidth(width), numberOfDiagonalDots(numberOfDiagonalDots),
    // ω = √(K / m)
    oscillationPeriod(std::sqrt(springConstant / objectMass)),
    springConstant(springConstant), objectMass(objectMass), frictionConstant(frictionConstant),
    strokeColor(strokeColor), QGraphicsItem(parent), animated(true), timeLine(new QTimeLine(10000, this))
{
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(animationFrame(int)));
    timeLine->setCurveShape(QTimeLine::LinearCurve);
}

void GraphicsSpringItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(strokeColor);
    painter->drawLine(0,0,25,0);
    painter->drawLine(25, 0, (width-25)/numberOfDiagonalDots + 25, -int(height/2)); // First diagonal
    int x2 = int(height/2);
    for (int i = 1; i < numberOfDiagonalDots-1; ++i) {
        painter->drawLine(i*(width-25)/numberOfDiagonalDots + 25, -x2, (i+1)*(width-25)/numberOfDiagonalDots + 25, x2);
        x2 *= -1;
    }
    painter->drawLine((numberOfDiagonalDots-1)*(width-25)/numberOfDiagonalDots + 25, -x2, width, 0); // Last diagonal
}

QRectF GraphicsSpringItem::boundingRect() const {
    return QRectF(0, -int(height/2), width, height);
}

void GraphicsSpringItem::stopAnimation() {
    animated = false;
    timeLine->stop();
}

void GraphicsSpringItem::startAnimation() {
    releaseWidth = width;
    animated = true;
    calcAnimation();
    timeLine->start();
}

void GraphicsSpringItem::updateSpring(QPointF variationDistance) {
    width = (width + variationDistance.x() > 25)? width + variationDistance.x() : width;
    prepareGeometryChange();
    update(x(), y(), width, height);
}

void GraphicsSpringItem::animationFrame(int frame) {
    int lastWidth = width;
    /* x(t) = A * e^(-γt) * cos(ωt)
     * avec A la longueur du ressort avant relâchement
     * γ le coefficient de frottement
     * ω la pseudo-periode
     */
    width = int((releaseWidth - initialWidth) * std::exp(-frictionConstant * frame/60.) * std::cos(oscillationPeriod*frame/60.) + initialWidth);
    width = (width < 0)? 0 : width;
    prepareGeometryChange();
    update(x(), y(), width, height);
    emit springGeometryAnimationChange(width - lastWidth);
}

void GraphicsSpringItem::calcAnimation() {
    timeLine->setFrameRange(0,5999);
}

void GraphicsSpringItem::setSpringConstant(float springConstant)
{
    this->springConstant = springConstant;
    oscillationPeriod = std::sqrt(springConstant / objectMass);
}

void GraphicsSpringItem::setSpringConstant(double springConstant)
{
    this->springConstant = float(springConstant);
    oscillationPeriod = float(std::sqrt(springConstant / objectMass));
}

void GraphicsSpringItem::setFrictionConstant(float frictionConstant)
{
    this->frictionConstant = frictionConstant;
}

void GraphicsSpringItem::setFrictionConstant(double frictionConstant)
{
    this->frictionConstant = float(frictionConstant);
}

void GraphicsSpringItem::setObjectMass(float objectMass)
{
    this->objectMass = objectMass;
    oscillationPeriod = std::sqrt(springConstant / objectMass);
}

void GraphicsSpringItem::setObjectMass(double objectMass)
{
    this->objectMass = float(objectMass);
    oscillationPeriod = float(std::sqrt(springConstant / objectMass));
}
