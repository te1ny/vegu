#include "main_window.hpp"
#include "ui_main_window.h"

#include <QHBoxLayout>

#include "tools/tool_bar.hpp"
#include "canvas/canvas.hpp"
#include "canvas/canvas_view.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);
    
    mToolBar = new ToolBar(this);
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, mToolBar);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* layout = new QHBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0 ,0);

    mCanvas = new Canvas(this);
    mCanvasView = new CanvasView(this);
    mCanvasView->setCanvas(mCanvas);
    layout->addWidget(mCanvasView);
    connect(mToolBar, &ToolBar::toolChanged, mCanvasView, &CanvasView::onToolChanged);

    mToolBar->changeTool("Line");
    mToolBar->setCanvasView(mCanvasView);
}

MainWindow::~MainWindow() {
    delete mUi;
}
