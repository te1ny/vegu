#ifndef RECTANGLE_OBJECT_HPP
#define RECTANGLE_OBJECT_HPP

#include "../scene_object.hpp"

class RectangleObject : public SceneObject {
public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    RectangleObject(const QRectF& rect, QGraphicsItem* parent = nullptr);

private:
    QRectF mRect;
};

#endif // RECTANGLE_OBJECT_HPP
