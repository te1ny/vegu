#include "line_tool.hpp"

#include "../canvas/canvas_view.hpp"

void LineTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mItem)
        return;
    mStartPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem = new QGraphicsLineItem(QLineF(mStartPosition, mStartPosition));
    mItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    mCanvasView->scene()->addItem(mItem);
}

void LineTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setLine(QLineF(mStartPosition, lastPosition));
}

void LineTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setLine(QLineF(mStartPosition, lastPosition));
    mItem = nullptr;
}
