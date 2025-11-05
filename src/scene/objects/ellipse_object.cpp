#include "ellipse_object.hpp"

#include <QPainter>

QRectF EllipseObject::boundingRect() const {
    return mRect;
}

void EllipseObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawEllipse(mRect);
}

EllipseObject::EllipseObject(
        const QRectF& rect, 
        QGraphicsItem* parent)
    : SceneObject(parent)
    , mRect(rect)
{
}
