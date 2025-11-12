#ifndef LINE_TOOL_HPP
#define LINE_TOOL_HPP

#include <QGraphicsLineItem>
#include <QPoint>

#include "tool.hpp"

class LineTool : public Tool {
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF mStartPosition;
    QGraphicsLineItem* mItem{};
}; 

#endif // CIRCLE_TOOL_HPP
