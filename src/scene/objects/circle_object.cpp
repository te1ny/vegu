#include "circle_object.hpp"

#include <QPainter>

QRectF CircleObject::boundingRect() const {
    return mRect;
}

void CircleObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawEllipse(mRect);
}

CircleObject::CircleObject(
        const QRectF& rect, 
        QGraphicsItem* parent)
    : SceneObject(parent)
    , mRect(rect)
{
}
