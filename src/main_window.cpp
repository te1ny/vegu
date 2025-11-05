#include "main_window.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    mToolBar = new ToolBar(this);

    addToolBar(mToolBar);
}

MainWindow::~MainWindow() {
    delete mUi;
}
