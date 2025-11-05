#ifndef LINE_OBJECT_HPP
#define LINE_OBJECT_HPP

#include "../scene_object.hpp"

class LineObject : public SceneObject {
public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    LineObject(const QLineF& line, QGraphicsItem* parent = nullptr);

private:
    QLineF mLine;
};

#endif // LINE_OBJECT_HPP
