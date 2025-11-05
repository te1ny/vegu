#include "main_window.hpp"
#include "inspector/inspector.hpp"
#include "scene/scene.hpp"
#include "scene/scene_tree.hpp"
#include "ui_main_window.h"
#include "viewport/viewport.hpp"

#include <QWidget>
#include <QSplitter>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);
    
    mScene = new Scene(this);
    mViewport = new Viewport(mScene, this);
    mSceneTree = new SceneTree(this);
    mSceneTree->setScene(mScene);
    mInspector = new Inspector(this);
    mToolBar = new ToolBar(this);
    mToolBar->setViewport(mViewport);

    addToolBar(mToolBar);

    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mViewport);
    splitter->addWidget(mSceneTree);
    splitter->addWidget(mInspector);
    
    setCentralWidget(splitter);

    connect(mScene, &Scene::objectSelected, mInspector, &Inspector::setObject);
}

MainWindow::~MainWindow() {
    delete mUi;
}
