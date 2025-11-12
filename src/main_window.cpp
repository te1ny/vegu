#include "main_window.hpp"
#include "ui_main_window.h"

#include <QHBoxLayout>
#include <QFileDialog>

#include "tools/tool_bar.hpp"
#include "canvas/canvas.hpp"
#include "canvas/canvas_view.hpp"
#include "bars/menu_bar.hpp"
#include "canvas/canvas_loader.hpp"
#include "action_manager/action_manager.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    ActionManager::instance(this);

    mToolBar = new ToolBar(this);
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, mToolBar);
    
    mMenuBar = new MenuBar(this);
    setMenuBar(mMenuBar);

    connect(mMenuBar, &MenuBar::save, this, &MainWindow::onSave);
    connect(mMenuBar, &MenuBar::load, this, &MainWindow::onLoad);

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

void MainWindow::onSave() {
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить TOML"), "", "TOML Files (*.toml)");
    if (fileName.isEmpty())
        return;
    CanvasLoader::saveToToml(mCanvas, fileName);
}

void MainWindow::onLoad() {
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Загрузить TOML"), "", "TOML Files (*.toml)");
    if (fileName.isEmpty())
        return;
    
    CanvasLoader::loadFromToml(mCanvas, fileName);
}
