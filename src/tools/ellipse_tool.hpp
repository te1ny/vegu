#ifndef ELLIPSE_TOOL_HPP
#define ELLIPSE_TOOL_HPP

#include "tool.hpp"

class EllipseTool : public Tool {
public:
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF startPos;
};

#endif // ELLIPSE_TOOL_HPP
