#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>

class ToolBar;
class Canvas;
class CanvasView;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    ToolBar* mToolBar; 
    Canvas* mCanvas;
    CanvasView* mCanvasView;

    Ui::MainWindow* mUi;
};

#endif // MAIN_WINDOW_HPP
