#ifndef SCENE_TREE_HPP
#define SCENE_TREE_HPP

#include <QTreeWidget>

#include "scene.hpp"

class SceneTree : public QTreeWidget {
    Q_OBJECT

public:
    void setScene(Scene* scene);
    void contextMenuEvent(QContextMenuEvent* event);

    SceneTree(QWidget* parent = nullptr);

private slots:
    void updateTree();
    void onItemClicked(QTreeWidgetItem* item, int column);
    void showContextMenu(const QPoint& position);

private:
    Scene* mScene;
};

#endif // SCENE_TREE_HPP
