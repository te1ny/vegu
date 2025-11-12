#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>

class ToolBar;
class Canvas;
class CanvasView;
class MenuBar;
class CanvasLoader;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void onSave();
    void onLoad();

private:
    ToolBar* mToolBar; 
    Canvas* mCanvas;
    CanvasView* mCanvasView;
    MenuBar* mMenuBar;
    CanvasLoader* mCanvasLoader;

    Ui::MainWindow* mUi;
};

#endif // MAIN_WINDOW_HPP
