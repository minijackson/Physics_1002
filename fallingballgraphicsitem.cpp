#include "fallingballgraphicsitem.h"

#include <boost/math/special_functions/pow.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>
#include <boost/math/special_functions/round.hpp>

FallingBallGraphicsItem::FallingBallGraphicsItem(qreal posX, qreal posY, qreal ballWidth, qreal ballHeight, int windowHeight) :
    QGraphicsEllipseItem(posX, posY, ballWidth, ballHeight),
    height(ballHeight), width(ballWidth), windowHeight(windowHeight)
{
    setCursor(Qt::OpenHandCursor);

    timeLine = new QTimeLine(0);
    animation = new QGraphicsItemAnimation;

    calcAnimation();
}

void FallingBallGraphicsItem::calcAnimation() {

    qreal startingPosY = this->scenePos().y();
    qreal currentPosY = 0;

    timeLine->setFrameRange(0,100);

    // On prend 150px = 1m
    // On a t_max = sqrt(2*y_max / g)
    animationDuration = (int)boost::math::round(boost::math::sqrt1pm1(2*(windowHeight-startingPosY) / (9.81*150)-1) + 1);
    timeLine->setDuration(animationDuration * 1000);
    animation->setItem(this);
    animation->setTimeLine(timeLine);

    for (int t = 0; t < animationDuration*25; ++t) {
        // (1/2)*g*t²
        currentPosY = ((boost::math::pow<2>(t/25.0)/2)*9.81*150 + startingPosY < windowHeight)? (boost::math::pow<2>(t/25.0)/2)*9.81*150 + startingPosY : windowHeight;
        animation->setPosAt(t/(animationDuration*25.0), QPointF(this->x(), currentPosY));
    }
}

void FallingBallGraphicsItem::activateAnimation() {
    timeLine->start();
}

void FallingBallGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
    dragStartPos = this->pos();
}

void FallingBallGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
    this->calcAnimation();
    this->activateAnimation();
}

void FallingBallGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
             .length() < QApplication::startDragDistance()) {
             return;
    }

    this->setPos(this->dragStartPos + event->scenePos() - event->buttonDownScenePos(Qt::LeftButton));
}
