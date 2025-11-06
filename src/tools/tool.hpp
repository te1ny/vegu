#ifndef TOOL_HPP
#define TOOL_HPP

#include <QString>
#include <QIcon>
#include <QAction>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QColor>

class Tool : public QObject {
public:
    QAction* action();

    virtual void mousePressEvent(QMouseEvent* event) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event) = 0;

    QColor strokeColor();
    void setStrokeColor(const QColor& color);

    QColor fillColor();
    void setFillColor(const QColor& color);

    qreal strokeWidth();
    void setStrokeWidth(const qreal& width);

    Tool(const QString& name);
    virtual ~Tool() = default;

private:
    QPen mPenis; // hehe :D
    QBrush mBrush;
    QAction* mAction;
};

#endif // TOOL_HPP
