#ifndef CIRCLE_TOOL_HPP
#define CIRCLE_TOOL_HPP

#include "tool.hpp"

class CircleTool : public Tool {
public:
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF startPos;
};

#endif // CIRCLE_TOOL_HPP
