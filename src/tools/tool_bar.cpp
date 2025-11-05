#include "tool_bar.hpp"

#include <QVector>

#include "rectangle_tool.hpp"

ToolBar::ToolBar(QWidget* parent)
    : QToolBar(parent)
{
    setOrientation(Qt::Orientation::Vertical);

    mTools["Rectangle"] = new RectangleTool(QString("Rectangle"));
    mTools["Circle"] = new RectangleTool(QString("Circle"));
    mTools["Ellipse"] = new RectangleTool(QString("Ellipse"));
    mTools["Line"] = new RectangleTool(QString("Line"));

    for (const auto& toolName : mTools.keys()) {
        addTool(toolName);
    }
}

void ToolBar::addTool(const QString& toolName) {
    auto* action = mTools[toolName]->action();
    connect(action, &QAction::triggered, [this, toolName]{
        emit toolChanged(mTools[toolName]);
    });
    addAction(action);
}
