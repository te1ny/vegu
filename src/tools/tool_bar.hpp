#ifndef TOOL_BAR_HPP
#define TOOL_BAR_HPP

#include <QToolBar>
#include <QAction>
#include <QString>
#include <QMap>

#include "tool.hpp"

class ToolBar : public QToolBar {
    Q_OBJECT

public:
    void changeTool(const QString& toolName);

    ToolBar(QWidget* parent = nullptr);

signals:
    void toolChanged(Tool* tool);

private:
    void addTool(const QString& toolName);

    QMap<QString, Tool*> mTools;
};

#endif // TOOL_BAR_HPP
