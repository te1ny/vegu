#ifndef TOOL_HPP
#define TOOL_HPP

#include <QString>
#include <QIcon>
#include <QAction>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QGraphicsItem>

class CanvasView;

class Tool : public QObject {
public:
    QAction* action() const;

    virtual void mousePressEvent(QMouseEvent* event) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event) = 0;

    QColor strokeColor() const;
    void setStrokeColor(const QColor& color);

    QColor fillColor() const;
    void setFillColor(const QColor& color);

    qreal strokeWidth() const;
    void setStrokeWidth(const qreal& width);

    virtual void setCanvasView(CanvasView* canvasView);

    Tool(const QString& name);
    virtual ~Tool() = default;

protected:
    QPen mPenis; // hehe :D
    QBrush mBrush;
    QAction* mAction;
    CanvasView* mCanvasView;
};

#endif // TOOL_HPP
