#include "selection_tool.hpp"

#include "../viewport/viewport.hpp"

void SelectionTool::mousePressEvent(QMouseEvent* event) {
    auto position = mViewport->mapToScene(event->pos());
    auto item = mScene->itemAt(position, QTransform());
    if (item) {
        item->setSelected(true);
        emit mScene->objectSelected(dynamic_cast<SceneObject*>(item));
    }
}
