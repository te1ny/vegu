#ifndef CIRCLE_OBJECT_HPP
#define CIRCLE_OBJECT_HPP

#include "../scene_object.hpp"

class CircleObject : public SceneObject {
public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    CircleObject(const QRectF& rect, QGraphicsItem* parent = nullptr);

private:
    QRectF mRect;
};

#endif // CIRCLE_OBJECT_HPP
