#ifndef TOOL_BAR_HPP
#define TOOL_BAR_HPP

#include <QToolBar>
#include <QAction>
#include <QString>
#include <QMap>
#include <QColorDialog>

#include "tool.hpp"

class CanvasVies;

class ToolBar : public QToolBar {
    Q_OBJECT

public:
    void changeTool(const QString& toolName);
    void setCanvasView(CanvasView* canvasView);

    ToolBar(QWidget* parent = nullptr);

signals:
    void toolChanged(Tool* tool);

private:
    void addTool(const QString& toolName);

    QMap<QString, Tool*> mTools;
    QColorDialog* mStrokeColorSettings;
    QColorDialog* mFillColorSettings;
};

#endif // TOOL_BAR_HPP
