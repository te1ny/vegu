#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>

#include "tools/tool_bar.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    ToolBar* mToolBar; 

    Ui::MainWindow* mUi;
};

#endif // MAIN_WINDOW_HPP
