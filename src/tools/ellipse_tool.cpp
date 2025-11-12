#include "ellipse_tool.hpp"

#include "../canvas/canvas_view.hpp"

void EllipseTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mItem)
        return;
    mStartPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem = new QGraphicsEllipseItem(QRectF(mStartPosition, mStartPosition).normalized());
    mItem->setCacheMode(QGraphicsItem::NoCache);
    mItem->setPen(mPenis);
    mItem->setBrush(mBrush);
    mItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    mCanvasView->scene()->addItem(mItem);
}

void EllipseTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setRect(QRectF(mStartPosition, lastPosition).normalized());
}

void EllipseTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mItem)
        return;
    auto lastPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem->setRect(QRectF(mStartPosition, lastPosition).normalized());
    mItem = nullptr;
}
