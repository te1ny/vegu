#include "rectangle_object.hpp"

#include <QPainter>

QRectF RectangleObject::boundingRect() const {
    return mRect;
}

void RectangleObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawRect(mRect);
}

RectangleObject::RectangleObject(
        const QRectF& rect, 
        QGraphicsItem* parent)
    : SceneObject(parent)
    , mRect(rect)
{
}
