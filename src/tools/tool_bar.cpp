#include "tool_bar.hpp"

#include "selection_tool.hpp"
#include "move_tool.hpp"
#include "rectangle_tool.hpp"
#include "circle_tool.hpp"
#include "ellipse_tool.hpp"
#include "line_tool.hpp"

void ToolBar::setViewport(Viewport* viewport) {
    addToolButton(new SelectionTool(viewport), "Selection", QIcon());
    addToolButton(new MoveTool(viewport),      "Move",      QIcon());
    addToolButton(new RectangleTool(viewport), "Rectangle", QIcon());
    addToolButton(new CircleTool(viewport),    "Circle",    QIcon());
    addToolButton(new EllipseTool(viewport),   "Ellipse",   QIcon());
    addToolButton(new LineTool(viewport),      "Line",      QIcon());
}

ToolBar::ToolBar(QWidget* parent) 
    : QToolBar(parent)
    , mCurrentTool(nullptr)
{
} 

void ToolBar::addToolButton(Tool* tool, const QString& name, const QIcon& icon) {
    QAction* action = addAction(icon, name);
    connect(action, &QAction::triggered, [this, tool]{
        if (mCurrentTool)
            mCurrentTool->deactivate();
        mCurrentTool = tool;
        mCurrentTool->activate();
    });
}
