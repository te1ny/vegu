#include "scaling_tool.hpp"

#include "../canvas/canvas_view.hpp"
#include "../canvas/canvas.hpp"

#include <QVector2D>

void ScalingTool::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || mGroup)
        return;
    auto scene = dynamic_cast<Canvas*>(mCanvasView->scene());
    if (scene->selectedItems().isEmpty())
        return;

    QRectF boundingRect;
    for (auto item : scene->selectedItems()) {
        boundingRect = boundingRect.united(item->sceneBoundingRect());
    }
    mOrigin = boundingRect.center();

    mGroup = scene->createItemGroup(scene->selectedItems());
    mGroup->setTransformOriginPoint(mOrigin);

    auto mousePosition = mCanvasView->mapToScene(event->pos());
    QVector2D vector(mousePosition - mOrigin);
    mPreviousDistance = vector.length();
}

void ScalingTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mGroup)
        return;
    auto scenePos = mCanvasView->mapToScene(event->pos());
    QVector2D vec(scenePos - mOrigin);
    auto currDistance = vec.length();
    if (qFuzzyCompare(mPreviousDistance, 0.0))
        return;
    auto factor = currDistance / mPreviousDistance;
    mGroup->setScale(mGroup->scale() * factor);
    mPreviousDistance = currDistance;
}

void ScalingTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mGroup)
        return;
    mCanvasView->scene()->destroyItemGroup(mGroup);
    mGroup = nullptr;
}
