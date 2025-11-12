#include "rectangle_tool.hpp"

#include "../canvas/canvas_view.hpp"
#include "../action_manager/action_manager.hpp"

void RectangleTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mItem)
        return;
    mStartPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem = new QGraphicsRectItem(QRectF(mStartPosition, mStartPosition).normalized());
    mItem->setCacheMode(QGraphicsItem::NoCache);
    mItem->setPen(mPenis);
    mItem->setBrush(mBrush);
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
    ActionManager::instance().add("Remove Rectangle", "Place Rectangle",
            [item = mItem](){
                item->hide();
                item->setFlag(QGraphicsItem::ItemIsSelectable, false);
            },
            [item = mItem](){
                item->show();
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            });
    mItem = nullptr;
}
