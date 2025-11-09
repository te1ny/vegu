#include "selection_tool.hpp"

#include <QRect>

#include "../canvas/canvas_view.hpp"

void SelectionTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mRubberBand)
        return;
    mStartPosition = event->position().toPoint();
    mRubberBand = new QRubberBand(QRubberBand::Rectangle, mCanvasView);
    mRubberBand->setGeometry(QRect(mStartPosition, mStartPosition).normalized());
    mRubberBand->show();
    select();
}

void SelectionTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mRubberBand)
        return;
    auto lastPosition = event->position().toPoint();
    mRubberBand->setGeometry(QRect(mStartPosition, lastPosition).normalized());
    select();
}

void SelectionTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mRubberBand)
        return;
    delete mRubberBand;
    mRubberBand = nullptr;
}

void SelectionTool::setCanvasView(CanvasView* canvasView) {
    mCanvasView = canvasView;
    connect(this, &SelectionTool::selectItem, canvasView, &CanvasView::onItemSelected);
    connect(this, &SelectionTool::unselectItem, canvasView, &CanvasView::onItemUnselected);
}

void SelectionTool::select() {
    QRect viewRect = mRubberBand->geometry();
    QPolygonF scenePoly = mCanvasView->mapToScene(viewRect);
    QRectF sceneRect = scenePoly.boundingRect();
    
    QList<QGraphicsItem*> itemsInRect = mCanvasView->scene()->items(sceneRect, Qt::IntersectsItemShape);
    QList<QGraphicsItem*> currentSelected;
    
    for (QGraphicsItem* item : itemsInRect) {
        if (item->flags() & QGraphicsItem::ItemIsSelectable) {
            currentSelected.append(item);
        }
    }
    
    for (QGraphicsItem* item : currentSelected) {
        if (!mSelectedItems.contains(item)) {
            emit selectItem(item);
        }
    }
    
    for (QGraphicsItem* item : mSelectedItems) {
        if (!currentSelected.contains(item)) {
            emit unselectItem(item);
        }
    }
    
    mSelectedItems = currentSelected;
}
