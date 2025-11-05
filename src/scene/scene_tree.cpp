#include "scene_tree.hpp"

#include <QMenu>
#include <QContextMenuEvent>

void SceneTree::setScene(Scene* scene) {
    mScene = scene;
    connect(mScene, &Scene::sceneChanged, this, &SceneTree::updateTree);
    updateTree();
}

void SceneTree::contextMenuEvent(QContextMenuEvent* event) {
    showContextMenu(event->pos());
}

SceneTree::SceneTree(QWidget* parent) 
    : QTreeWidget(parent)
    , mScene(nullptr)
{
    setHeaderLabel("Scene Tree");
    setDragDropMode(InternalMove);
    setSelectionMode(ExtendedSelection);
}

void SceneTree::updateTree() {
    clear();
    auto root = new QTreeWidgetItem(this, { "root" });
    for (auto item : mScene->items()) {
        if (auto obj = dynamic_cast<SceneObject*>(item)) {
            auto child = new QTreeWidgetItem(root, {obj->data(0).toString()});
            child->setData(0, Qt::UserRole, QVariant::fromValue(obj));
        }
    }
    expandAll();
}

void SceneTree::onItemClicked(QTreeWidgetItem* item, int column) {
    if (auto obj = item->data(0, Qt::UserRole).value<SceneObject*>()) {
        mScene->clearSelection();
        obj->setSelected(true);
        emit mScene->objectSelected(obj);
    }
}

void SceneTree::showContextMenu(const QPoint& position) {
    QTreeWidgetItem* item = itemAt(position);
    if (!item)
        return;
    
    QMenu menu;
    QAction* deleteAction = menu.addAction("Delete");
    connect(deleteAction, &QAction::triggered, [this, item]{
        if (auto obj = item->data(0, Qt::UserRole).value<SceneObject*>())
            mScene->remove(obj);
    });
    menu.exec(viewport()->mapToGlobal(position));
}
