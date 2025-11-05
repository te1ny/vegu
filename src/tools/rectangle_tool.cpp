#include "rectangle_tool.hpp"

#include "../scene/objects/rectangle_object.hpp"
#include "../viewport/viewport.hpp"

void RectangleTool::mousePressEvent(QMouseEvent* event) {
    startPos = mViewport->mapToScene(event->pos());
}

void RectangleTool::mouseMoveEvent(QMouseEvent* event) {

}

void RectangleTool::mouseReleaseEvent(QMouseEvent* event) {
    auto endPos = mViewport->mapToScene(event->pos());
    QRectF rect(startPos, endPos);
    auto object = new RectangleObject(rect.normalized());
    mScene->add(object);
}
