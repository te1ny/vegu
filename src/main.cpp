#include <QApplication>

#include "main_window.hpp"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    MainWindow window;
    window.show();

    // Maybe add threads for save/load svg

    int error = a.exec();
    return error;
}
