#ifndef RECTANGLE_TOOL_HPP
#define RECTANGLE_TOOL_HPP

#include "tool.hpp"

class RectangleTool : public Tool {
public:
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF startPos;
};

#endif // RECTANGLE_TOOL_HPP
