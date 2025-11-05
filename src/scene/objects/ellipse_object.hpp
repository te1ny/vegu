#ifndef ELLIPSE_OBJECT_HPP
#define ELLIPSE_OBJECT_HPP

#include "../scene_object.hpp"

class EllipseObject : public SceneObject {
public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    EllipseObject(const QRectF& rect, QGraphicsItem* parent = nullptr);

private:
    QRectF mRect;
};

#endif // ELLIPSE_OBJECT_HPP
