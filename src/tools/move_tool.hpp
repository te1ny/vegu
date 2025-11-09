#ifndef MOVE_TOOL_HPP
#define MOVE_TOOL_HPP

#include <QPoint>

#include "tool.hpp"

class MoveTool : public Tool {
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF* mPreviousPosition{};
}; 

#endif // MOVE_TOOL_HPP
