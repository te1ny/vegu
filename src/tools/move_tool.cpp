#include "move_tool.hpp"

#include "../canvas/canvas_view.hpp"

void MoveTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mPreviousPosition)
        return;
    mPreviousPosition = new QPointF(mCanvasView->mapToScene(event->position().toPoint()));
}

void MoveTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mPreviousPosition)
        return;

    auto currentPosition = mCanvasView->mapToScene(event->position().toPoint());
    auto delta = currentPosition - *mPreviousPosition;

    for (auto item : mCanvasView->scene()->selectedItems())
        item->moveBy(delta.x(), delta.y());

    *mPreviousPosition = currentPosition;
}

void MoveTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mPreviousPosition)
        return;
    delete mPreviousPosition;
    mPreviousPosition = nullptr;
}
