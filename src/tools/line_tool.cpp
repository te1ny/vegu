#include "line_tool.hpp"

#include "../canvas/canvas_view.hpp"
#include "../action_manager/action_manager.hpp"

void LineTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mItem)
        return;
    mStartPosition = mCanvasView->mapToScene(event->position().toPoint());
    mItem = new QGraphicsLineItem(QLineF(mStartPosition, mStartPosition));
    mItem->setCacheMode(QGraphicsItem::NoCache);
    mItem->setPen(mPenis);
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
    ActionManager::instance().add("Remove Line", "Place Line",
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
