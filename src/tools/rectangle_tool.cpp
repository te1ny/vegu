#include "rectangle_tool.hpp"

#include "../canvas/canvas_view.hpp"

void RectangleTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mItem)
        return;
    mStartPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem = new QGraphicsRectItem(QRectF(mStartPosition, mStartPosition).normalized());
    mItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    mCanvasView->scene()->addItem(mItem);
}

void RectangleTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setRect(QRectF(mStartPosition, lastPosition).normalized());
}

void RectangleTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setRect(QRectF(mStartPosition, lastPosition).normalized());
    mItem = nullptr;
}
