#include "scene.hpp"

#include "../action_manager/action_manager.hpp"
#include <qgraphicsscene.h>

void Scene::add(SceneObject* object) {
    addItem(object);

    auto undo = [this, object]{ 
        removeItem(object); 
    };

    auto redo = [this, object]{ 
        addItem(object);
    };

    ActionManager::instance().add("Delete object", "Return object", std::move(undo), std::move(redo));

    emit sceneChanged();
}

void Scene::remove(SceneObject* object) {
    removeItem(object);

    auto undo = [this, object]{ 
        addItem(object); 
    };

    auto redo = [this, object]{ 
        removeItem(object);
    };

    ActionManager::instance().add("Return object", "Delete object", std::move(undo), std::move(redo));

    emit sceneChanged();
}

QList<SceneObject*> Scene::selectedObjects() {
    QList<SceneObject*> objects{};
    auto items = selectedItems();

    objects.reserve(items.count());
    for (auto item : items) {
        if (auto object = dynamic_cast<SceneObject*>(item))
            objects.append(object);
    }

    return objects;
}

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
{
}
