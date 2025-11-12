#ifndef ROTATION_TOOL_HPP
#define ROTATION_TOOL_HPP

#include <QGraphicsItemGroup>
#include <QPointF>

#include "tool.hpp"

class RotationTool : public Tool {
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF mOrigin;
    qreal mStartAngle{};
    QGraphicsItemGroup* mGroup{};
}; 

#endif // ROTATION_TOOL_HPP
