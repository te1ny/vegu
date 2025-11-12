#include "tool_bar.hpp"

#include <QVector>
#include <QSpinBox>
#include <qspinbox.h>

#include "move_tool.hpp"
#include "selection_tool.hpp"
#include "rotation_tool.hpp"
#include "scaling_tool.hpp"
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
    setIconSize(QSize(40, 40));

    mTools["Move"] = new MoveTool(QString("Move"));
    mTools["Selection"] = new SelectionTool(QString("Selection"));
    mTools["Rotation"] = new RotationTool(QString("Rotation"));
    mTools["Scaling"] = new ScalingTool(QString("Scaling"));
    mTools["Ellipse"] = new EllipseTool(QString("Ellipse"));
    mTools["Rectangle"] = new RectangleTool(QString("Rectangle"));
    mTools["Line"] = new LineTool(QString("Line"));
    mTools["Circle"] = new CircleTool(QString("Circle"));

    addTool("Move");
    addTool("Selection");
    addTool("Rotation");
    addTool("Scaling");
    addTool("Ellipse");
    addTool("Rectangle");
    addTool("Line");
    addTool("Circle");

    auto* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(spacer);

    auto* spinBox = new QDoubleSpinBox();
    addWidget(spinBox);

    mFillColorSettings = new QColorDialog(parent);   
    mStrokeColorSettings = new QColorDialog(parent);   

    for (auto tool : mTools.values()) {
        connect(spinBox, &QDoubleSpinBox::valueChanged, [tool](qreal value){
            tool->setStrokeWidth(value);
        });
        connect(mStrokeColorSettings, &QColorDialog::colorSelected, [tool](const QColor& color){
            tool->setStrokeColor(color);
        });
        connect(mFillColorSettings, &QColorDialog::colorSelected, [tool](const QColor& color){
            tool->setFillColor(color);
        });
    }

    QAction* strokeAction = new QAction("Stroke Color");
    QAction* fillAction = new QAction("Fill Color");

    connect(strokeAction, &QAction::triggered, [this]{
        mStrokeColorSettings->show();
    });
    connect(fillAction, &QAction::triggered, [this]{
        mFillColorSettings->show();
    });
    
    addAction(strokeAction);
    addAction(fillAction);
}

void ToolBar::addTool(const QString& toolName) {
    auto* action = mTools[toolName]->action();
    connect(action, &QAction::triggered, [this, toolName]{
        emit toolChanged(mTools[toolName]);
    });
    addAction(action);
}
