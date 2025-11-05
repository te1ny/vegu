#include "viewport.hpp"

#include "../tools/tool.hpp"
#include <qgraphicsview.h>


Viewport::Viewport(Scene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
    setDragMode(RubberBandDrag);
    setInteractive(true);
}

void Viewport::wheelEvent(QWheelEvent* event) {
    qreal factor = 1.15;
    if (event->angleDelta().y() < 0) factor = 1 / factor;
    scale(factor, factor);
}

void Viewport::mousePressEvent(QMouseEvent* event) {
    if (mCurrentTool)
        mCurrentTool->mousePressEvent(event);
    else
        QGraphicsView::mousePressEvent(event);
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
    if (mCurrentTool)
        mCurrentTool->mouseMoveEvent(event);
    else
        QGraphicsView::mouseMoveEvent(event);
}

void Viewport::mouseReleaseEvent(QMouseEvent* event) {
    if (mCurrentTool)
        mCurrentTool->mouseReleaseEvent(event);
    else
        QGraphicsView::mouseReleaseEvent(event);
}
