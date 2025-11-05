#include <QApplication>

#include "main_window.hpp"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    MainWindow window;
    window.show();

    int error = a.exec();
    return error;
}
