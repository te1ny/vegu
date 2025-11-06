#ifndef SELECTION_TOOL_HPP
#define SELECTION_TOOL_HPP

#include "tool.hpp"

class SelectionTool : public Tool {
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
}; 

#endif // SELECTION_TOOL_HPP
