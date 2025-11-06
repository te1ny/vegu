#include "main_window.hpp"
#include "ui_main_window.h"

#include <QHBoxLayout>

#include "tools/tool_bar.hpp"

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

    //mViewport = new Viewport(this);
    //layout->addWidget(mViewport);
    //connect(mToolBar, &ToolBar::toolChanged, mViewport, &Viewport::onToolChanged);

    mToolBar->changeTool("Line");
}

MainWindow::~MainWindow() {
    delete mUi;
}
