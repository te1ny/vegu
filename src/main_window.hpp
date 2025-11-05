#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>

#include "scene/scene.hpp"
#include "scene/scene_tree.hpp"
#include "inspector/inspector.hpp"
#include "tools/tool_bar.hpp"
#include "viewport/viewport.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Scene* mScene;
    SceneTree* mSceneTree;
    Inspector* mInspector;
    Viewport* mViewport;
    ToolBar* mToolBar;

    Ui::MainWindow* mUi;
};

#endif // MAIN_WINDOW_HPP
