#include "line_object.hpp"

#include <QPainter>

QRectF LineObject::boundingRect() const {
    return QRectF(mLine.p1(), mLine.p2());
}

void LineObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(mPen);
    painter->drawLine(mLine);
}

LineObject::LineObject(
        const QLineF& line, 
        QGraphicsItem* parent)
    : SceneObject(parent)
    , mLine(line)
{
}
