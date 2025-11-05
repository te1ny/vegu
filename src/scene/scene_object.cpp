#include "scene_object.hpp"

#include "../action_manager/action_manager.hpp"

QPointF SceneObject::position() const {
    return mPosition;
}

void SceneObject::setPosition(QPointF position) {
    mPosition = position;
}

qreal SceneObject::rotation() const {
    return mRotation;
}

void SceneObject::setRotation(qreal rotation) {
    mRotation = rotation;
}

qreal SceneObject::scale() const {
    return mScale;
}

void SceneObject::setScale(qreal scale) {
    mScale = scale;
}

qreal SceneObject::layer() const {
    return mLayer;
}

void SceneObject::setLayer(qreal layer) {
    mLayer = layer;
}

QColor SceneObject::fillColor() const {
    return mBrush.color();
}

void SceneObject::setFillColor(const QColor& color) {
    mBrush.setColor(color);
    update();

    auto undo = [this, old = mBrush.color()]{ 
        mBrush.setColor(old);
        update();
    };

    auto redo = [this, color]{ 
        mBrush.setColor(color);
        update();
    };

    ActionManager::instance().add("Unset fill color", "Set fill color", std::move(undo), std::move(redo));
}

QColor SceneObject::strokeColor() const {
    return mPen.color();
}

void SceneObject::setStrokeColor(const QColor& color) {
    mPen.setColor(color);
    update();

    auto undo = [this, old = mPen.color()]{ 
        mPen.setColor(old);
        update();
    };

    auto redo = [this, color]{ 
        mPen.setColor(color);
        update();
    };

    ActionManager::instance().add("Unset stroke color", "Set stroke color", std::move(undo), std::move(redo));
}

SceneObject::SceneObject(QGraphicsItem* parent) : QGraphicsObject(parent)
{
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    mPen = QPen(Qt::black);
    mBrush = QBrush(Qt::NoBrush);
}
