#ifndef SELECTION_TOOL_HPP
#define SELECTION_TOOL_HPP

#include <QRubberBand>
#include <QPoint>
#include <QGraphicsRectItem>

#include "tool.hpp"

class SelectionTool : public Tool {
    Q_OBJECT

    using Tool::Tool;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void setCanvasView(CanvasView* canvasView) override;

signals:
    void selectItem(QGraphicsItem* item);
    void unselectItem(QGraphicsItem* item);

private:
    void select();

    QPoint mStartPosition;
    QRubberBand* mRubberBand{};
    QList<QGraphicsItem*> mSelectedItems{};
}; 

#endif // SELECTION_TOOL_HPP
