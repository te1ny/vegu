#ifndef TOOL_BAR_HPP
#define TOOL_BAR_HPP

#include <QToolBar>

#include "tool.hpp"
#include "../viewport/viewport.hpp"

class ToolBar : public QToolBar {
public:
    void setViewport(Viewport* viewport);

    ToolBar(QWidget* parent = nullptr);

private:
    void addToolButton(Tool* tool, const QString& name, const QIcon& icon);

    Tool* mCurrentTool;
};

#endif // TOOL_BAR_HPP
