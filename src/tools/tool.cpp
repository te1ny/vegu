#include "tool.hpp"

#include "../canvas/canvas_view.hpp"

QAction* Tool::action() const {
    return mAction;
}

QColor Tool::strokeColor() const {
    return mPenis.color();
}

void Tool::setStrokeColor(const QColor& color) {
    mPenis.setColor(color);
}

QColor Tool::fillColor() const {
    return mBrush.color();
}

void Tool::setFillColor(const QColor& color) {
    mBrush.setColor(color);
}

qreal Tool::strokeWidth() const {
    return mPenis.widthF();
}

void Tool::setStrokeWidth(const qreal& width) {
    mPenis.setWidthF(width);
}

void Tool::setCanvasView(CanvasView* canvasView) {
    mCanvasView = canvasView;
}

Tool::Tool(const QString& name) {
    mAction = new QAction(QIcon("src/tools/icons/" + name.toLower() + "_tool.svg"), name);
}
