#ifndef MOVE_TOOL_HPP
#define MOVE_TOOL_HPP

#include "tool.hpp"

class MoveTool : public Tool {
public:
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // MOVE_TOOL_HPP
