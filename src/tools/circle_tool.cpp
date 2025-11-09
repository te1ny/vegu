#include "circle_tool.hpp"

#include "../canvas/canvas_view.hpp"

QRectF toSquare(const QRectF& rect, const QPointF& start, const QPointF& end);
    
void CircleTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mItem)
        return;
    mStartPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem = new QGraphicsEllipseItem(QRectF(mStartPosition, mStartPosition).normalized());
    mItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    mCanvasView->scene()->addItem(mItem);
}

void CircleTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setRect(toSquare(QRectF(mStartPosition, lastPosition).normalized(), mStartPosition, lastPosition));
}

void CircleTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setRect(toSquare(QRectF(mStartPosition, lastPosition).normalized(), mStartPosition, lastPosition));
    mItem = nullptr;
}

QRectF toSquare(const QRectF& rect, const QPointF& start, const QPointF& end) {
    auto result = rect;
    auto side = result.height() > result.width() ? result.height() : result.width();
    if (result.width() < side) {
        result.setWidth(side);
        if (end.x() < start.x()) {
            result.moveLeft(start.x() - side);
        }
    } else {
        result.setHeight(side);
        if (end.y() < start.y()) {
            result.moveTop(start.y() - side);
        }
    }
    return result;
}
