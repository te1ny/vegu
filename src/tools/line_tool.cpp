#include "line_tool.hpp"

#include "../scene/objects/line_object.hpp"
#include "../viewport/viewport.hpp"

void LineTool::mousePressEvent(QMouseEvent* event) {
    startPos = mViewport->mapToScene(event->pos());
}

void LineTool::mouseMoveEvent(QMouseEvent* event) { 

}

void LineTool::mouseReleaseEvent(QMouseEvent* event) {
    auto endPos = mViewport->mapToScene(event->pos());
    QLineF line(startPos, endPos);
    auto object = new LineObject(line);
    mScene->add(object);
}
