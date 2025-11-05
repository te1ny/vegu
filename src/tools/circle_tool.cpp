#include "circle_tool.hpp"

#include "../scene/objects/circle_object.hpp"
#include "../viewport/viewport.hpp"

void CircleTool::mousePressEvent(QMouseEvent* event) {
    startPos = mViewport->mapToScene(event->pos());
}

void CircleTool::mouseMoveEvent(QMouseEvent* event) { 

}

void CircleTool::mouseReleaseEvent(QMouseEvent* event) {
    auto endPos = mViewport->mapToScene(event->pos());
    QRectF rect(startPos, endPos);
    auto object = new CircleObject(rect.normalized());
    mScene->add(object);
}
