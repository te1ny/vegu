#include "canvas_view.hpp"

#include <QRubberBand>

#include "canvas.hpp"
#include "../tools/tool.hpp"

void CanvasView::setCanvas(Canvas* canvas) {
    setScene(canvas);
    scene()->setSceneRect(0, 0, 600, 800);
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

void CanvasView::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        const double factor = 1.1;
        
        QPointF delta = event->angleDelta();
        if (delta.y() == 0) {
            event->ignore();
            return;
        }
        bool zoomIn = (delta.y() > 0);
        double scaleFactor = zoomIn ? factor : 1.0 / factor;
        
        QPointF mouseViewportPos = event->position();
        QPointF mouseScenePosBefore = mapToScene(mouseViewportPos.toPoint());
        
        setTransformationAnchor(QGraphicsView::NoAnchor);
        scale(scaleFactor, scaleFactor);
        
        QPointF mouseScenePosAfter = mapToScene(mouseViewportPos.toPoint());
        QPointF diff = mouseScenePosAfter - mouseScenePosBefore;
        
        translate(diff.x(), diff.y());
        
        centerOn(mouseScenePosBefore);
        
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void CanvasView::drawBackground(QPainter* painter, const QRectF& rect) {
    painter->fillRect(rect, QBrush(Qt::lightGray));
    painter->setClipRect(sceneRect() & rect);
    painter->fillRect(sceneRect(), Qt::white);
}

CanvasView::CanvasView(QWidget* parent)
    : QGraphicsView(parent)
    , mTool(nullptr)
{
}

void CanvasView::onToolChanged(Tool* tool) {
    mTool = tool;
}

void CanvasView::onItemSelected(QGraphicsItem* item) {
    if (item->isSelected())
        return;
    item->setSelected(true);
}

void CanvasView::onItemUnselected(QGraphicsItem* item) {
    if (!item->isSelected())
        return;
    item->setSelected(false);
}
