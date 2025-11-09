#include "tool_bar.hpp"

#include <QVector>

#include "move_tool.hpp"
#include "selection_tool.hpp"
#include "ellipse_tool.hpp"
#include "rectangle_tool.hpp"
#include "line_tool.hpp"
#include "circle_tool.hpp"

void ToolBar::changeTool(const QString& toolName) {
    mTools[toolName]->action()->trigger();
}

void ToolBar::setCanvasView(CanvasView* canvasView) {
    for (auto tool : mTools.values()) {
        tool->setCanvasView(canvasView);
    }
}

ToolBar::ToolBar(QWidget* parent)
    : QToolBar(parent)
{
    mTools["Move"] = new MoveTool(QString("Move"));
    mTools["Selection"] = new SelectionTool(QString("Selection"));
    mTools["Ellipse"] = new EllipseTool(QString("Ellipse"));
    mTools["Rectangle"] = new RectangleTool(QString("Rectangle"));
    mTools["Line"] = new LineTool(QString("Line"));
    mTools["Circle"] = new CircleTool(QString("Circle"));

    addTool("Move");
    addTool("Selection");
    addTool("Ellipse");
    addTool("Rectangle");
    addTool("Line");
    addTool("Circle");

    setIconSize(QSize(40, 40));
}

void ToolBar::addTool(const QString& toolName) {
    auto* action = mTools[toolName]->action();
    connect(action, &QAction::triggered, [this, toolName]{
        emit toolChanged(mTools[toolName]);
    });
    addAction(action);
}
