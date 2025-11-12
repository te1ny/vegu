#include "rotation_tool.hpp"

#include "../canvas/canvas_view.hpp"
#include "../canvas/canvas.hpp"

#include <QVector2D>

void RotationTool::mousePressEvent(QMouseEvent* event) {
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
    mStartAngle = qAtan2(vector.y(), vector.x());
}

void RotationTool::mouseMoveEvent(QMouseEvent* event) {
    if (!mGroup)
        return;
    auto mousePosition = mCanvasView->mapToScene(event->pos());
    QVector2D vector(mousePosition - mOrigin);
    auto currAngle = qAtan2(vector.y(), vector.x());
    auto delta = currAngle - mStartAngle;
    mGroup->setRotation(mGroup->rotation() + delta * 180.0 / M_PI);
    mStartAngle = currAngle;
}

void RotationTool::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton || !mGroup)
        return;
    mCanvasView->scene()->destroyItemGroup(mGroup);
    mGroup = nullptr;
}
