#include "menu_bar.hpp"

#include <QMenu>

MenuBar::MenuBar(QWidget* parent)
    : QMenuBar(parent)
{
    QMenu* canvasMenu = new QMenu(QString::fromUtf8("Холст"), this);
    QAction* saveAction = canvasMenu->addAction(QString::fromUtf8("Сохранить в ..."));
    QAction* loadAction = canvasMenu->addAction(QString::fromUtf8("Загрузить из ..."));

    addMenu(canvasMenu);

    connect(saveAction, &QAction::triggered, this, &MenuBar::save);
    connect(loadAction, &QAction::triggered, this, &MenuBar::load);
}
