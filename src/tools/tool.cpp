#include "tool.hpp"

QAction* Tool::action() {
    return mAction;
}

QColor Tool::strokeColor() {
    return mPenis.color();
}

void Tool::setStrokeColor(const QColor& color) {
    mPenis.setColor(color);
}

QColor Tool::fillColor() {
    return mBrush.color();
}

void Tool::setFillColor(const QColor& color) {
    mBrush.setColor(color);
}

qreal Tool::strokeWidth() {
    return mPenis.widthF();
}

void Tool::setStrokeWidth(const qreal& width) {
    mPenis.setWidthF(width);
}

Tool::Tool(const QString& name) {
    mAction = new QAction(QIcon("src/tools/icons/" + name.toLower() + "_tool.png"), name);
}
