#ifndef MENU_BAR_HPP
#define MENU_BAR_HPP

#include <QMenuBar>

class MenuBar : public QMenuBar {
    Q_OBJECT

public:
    MenuBar(QWidget* parent = nullptr);

signals:
    void save();
    void load();
};

#endif // MENU_BAR_HPP
