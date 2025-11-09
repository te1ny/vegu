#include "canvas_view.hpp"

#include <QRubberBand>
#include <qdebug.h>
#include <qlogging.h>

#include "canvas.hpp"
#include "../tools/tool.hpp"

void CanvasView::setCanvas(Canvas* canvas) {
    setScene(canvas);
}

void CanvasView::mousePressEvent(QMouseEvent* event) {
    if (mTool)
        mTool->mousePressEvent(event);
    else
        QGraphicsView::mousePressEvent(event);
}

void CanvasView::mouseMoveEvent(QMouseEvent* event) {
    if (mTool)
        mTool->mouseMoveEvent(event);
    else
        QGraphicsView::mouseMoveEvent(event);
}

void CanvasView::mouseReleaseEvent(QMouseEvent* event) {
    if (mTool)
        mTool->mouseReleaseEvent(event);
    else
        QGraphicsView::mouseReleaseEvent(event);
}

CanvasView::CanvasView(QWidget* parent)
    : QGraphicsView(parent)
    , mTool(nullptr)
{
    //setDragMode(NoDrag);
    //setResizeAnchor(NoAnchor);
    //setTransformationAnchor(NoAnchor);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setSceneRect(0, 0, 2000, 2000);
}

void CanvasView::onToolChanged(Tool* tool) {
    mTool = tool;
}

void CanvasView::onItemSelected(QGraphicsItem* item) {
    if (item->isSelected())
        return;
    item->setSelected(true);
    QGraphicsRectItem* selectionRect = new QGraphicsRectItem(item);
    selectionRect->setRect(item->boundingRect());
    
    QPen pen(Qt::blue, 1, Qt::DashLine);
    selectionRect->setPen(pen);
    selectionRect->setBrush(Qt::NoBrush);
    selectionRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    selectionRect->setZValue(1.0);
}

void CanvasView::onItemUnselected(QGraphicsItem* item) {
    if (!item->isSelected())
        return;
    item->setSelected(false);
    for (auto item : item->childItems())
        delete item;
}
