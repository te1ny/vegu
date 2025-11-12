#ifndef SCALING_TOOL_HPP
#define SCALING_TOOL_HPP

#include <QGraphicsItemGroup>
#include <QPointF>

#include "tool.hpp"

class ScalingTool : public Tool {
    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF mOrigin{};
    qreal mPreviousDistance{};
    QGraphicsItemGroup* mGroup{};
};
#endif // SCALING_TOOL_HPP
