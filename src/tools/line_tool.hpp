#ifndef LINE_TOOL_HPP
#define LINE_TOOL_HPP

#include "tool.hpp"

class LineTool : public Tool {
public:
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF startPos;
};

#endif // LINE_TOOL_HPP
