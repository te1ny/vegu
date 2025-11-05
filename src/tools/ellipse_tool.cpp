#include "ellipse_tool.hpp"

#include "../scene/objects/ellipse_object.hpp"
#include "../viewport/viewport.hpp"

void EllipseTool::mousePressEvent(QMouseEvent* event) {
    startPos = mViewport->mapToScene(event->pos());
}

void EllipseTool::mouseMoveEvent(QMouseEvent* event) { 

}

void EllipseTool::mouseReleaseEvent(QMouseEvent* event) {
    auto endPos = mViewport->mapToScene(event->pos());
    QRectF rect(startPos, endPos);
    auto object = new EllipseObject(rect.normalized());
    mScene->add(object);
}
