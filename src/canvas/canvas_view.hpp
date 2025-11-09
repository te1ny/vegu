#ifndef CANVAS_VIEW_HPP
#define CANVAS_VIEW_HPP

#include <QGraphicsView>
#include <QMouseEvent>

class Canvas;
class Tool;

class CanvasView : public QGraphicsView {
    Q_OBJECT

public:
    void setCanvas(Canvas* canvas);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    CanvasView(QWidget* parent = nullptr);

public slots:
    void onToolChanged(Tool* tool);
    void onItemSelected(QGraphicsItem* item);
    void onItemUnselected(QGraphicsItem* item);

private:
    Tool* mTool;
};

#endif // CANVAS_VIEW_HPP
