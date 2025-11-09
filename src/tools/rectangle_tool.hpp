#ifndef RECTANGLE_TOOL_HPP
#define RECTANGLE_TOOL_HPP

#include <QGraphicsRectItem>
#include <QPoint>

#include "tool.hpp"

class RectangleTool : public Tool {
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF mStartPosition;
    QGraphicsRectItem* mItem{};
}; 

#endif // RECTANGLE_TOOL_HPP
