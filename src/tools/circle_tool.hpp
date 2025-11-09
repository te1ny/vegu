#ifndef CIRCLE_TOOL_HPP
#define CIRCLE_TOOL_HPP

#include <QGraphicsEllipseItem>
#include <QPoint>

#include "tool.hpp"

class CircleTool : public Tool {
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF mStartPosition;
    QGraphicsEllipseItem* mItem{};
}; 

#endif // CIRCLE_TOOL_HPP
